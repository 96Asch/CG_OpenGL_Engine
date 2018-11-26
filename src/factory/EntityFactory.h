#ifndef ENTITYFACTORY_H_
#define ENTITYFACTORY_H_

#include <bitset>
#include <vector>
#include <iterator>
#include <list>

#include "../component/Component.h"
#include "../allocator/TypeAllocator.h"
#include "Global.h"
#include "../engine/EntityId.h"
#include "../util/Serializable.h"

typedef std::bitset<Global::NUM_BITS> ComponentMask;
class Entity;

class BaseView;

class EntityFactory : public Serializable{

public:
	EntityFactory();
	~EntityFactory();

	template <typename T>
	class ViewIterator {
	public:
        typedef ViewIterator self_type;
        typedef Entity value_type;
        typedef Entity& reference;
        typedef std::forward_iterator_tag iterator_category;
        typedef int difference_type;

		self_type& operator++();

		bool operator==(const T &rhs) const;

        bool operator!=(const T &rhs) const;

		value_type operator*();

		const value_type operator*() const;

	protected:

		ViewIterator(EntityFactory* ef, const ComponentMask mask, uint32_t index);

		void next();

		inline bool condition();

		inline bool valid();

	private:
        EntityFactory* ef;
		ComponentMask mask;
		uint32_t index;
		uint32_t capacity;
		std::list<uint32_t>::iterator freeIterator;
	};


	class BaseView {
	public:
		class Iterator : public ViewIterator<Iterator> {
		public:
			Iterator(EntityFactory *ef, const ComponentMask &mask, const uint32_t &index)
                : ViewIterator<Iterator>(ef, mask, index) {
					ViewIterator<Iterator>::next();
				}
		};


		Iterator begin() { return Iterator(ef, mask, 0); }
		Iterator end() { return Iterator(ef, mask, uint32_t(ef->capacity())); }
		const Iterator begin() const { return Iterator(ef, mask, 0); }
		const Iterator end() const { return Iterator(ef, mask, ef->capacity()); }

	private:
		friend class EntityFactory;

		BaseView(EntityFactory *ef) : ef(ef) { mask.set(); }
		BaseView(EntityFactory *ef, ComponentMask mask) : ef(ef), mask(mask) {}

		EntityFactory *ef;
		ComponentMask mask;
	};

	//TODO Future implementation
	virtual void serialize(std::ofstream &stream) override;

	virtual bool deserialize(std::ifstream &stream) override;

	Entity createEntity();
	
	void destroyEntity(const EntityId &id);


	template <typename T>
	void addComponent(const EntityId &id, T &&component){
		const size_t bit = T::bit();
		TypeAllocator<T> *pool = AccomodateComponent<T>();
		new(pool->get(id.index)) T(component);
		masks[id.index].set(bit);
	}


	template <typename T>
	T * getComponent(const EntityId &id) {
		BlockAllocator * pool = components[T::bit()];
		return static_cast<T*>(pool->get(id.index));
	}

	template <typename T>
	T * getComponent(const EntityId &id) const{
		BlockAllocator * pool = components[T::bit()];
		return static_cast<const T*>(pool->get(id.index));
	}

	template <typename... Ts>
	BaseView withComponents() {
		auto mask = componentMask<Ts...>();
		return BaseView(this, mask);
	}

	template<typename T>
	bool hasComponent(const EntityId &id){
		const size_t bit = T::bit();
		if (bit >= components.size())
			return false;

        BlockAllocator * pool = components[bit];

		if (!pool || !masks[id.index][bit])
			return false;
		return true;

	}

	template <typename T>
	void removeComponent(const EntityId &id){
		const size_t bit = T::bit();
		BlockAllocator* pool = components[bit];
		masks[id.index].reset(bit);
		pool->destroy(id.index);
	}


	EntityId createId(uint32_t id){
		return {id, entityVersion[id]};
	}

	bool valid(const EntityId &id);

	size_t capacity();

    size_t numEntities();

    Entity get(const EntityId &id);

    ComponentMask getMask(const EntityId &id);

private:
	template <typename T>
	TypeAllocator<T>* AccomodateComponent(){
		const size_t bit = T::bit();
		if (components.size() <= bit) {
			components.resize(bit + 1, nullptr);
		}
		if (!components[bit]) {
			TypeAllocator<T> *pool = new TypeAllocator<T>();
			pool->expand(index);
			components[bit] = pool;
		}
		return static_cast<TypeAllocator<T>*>(components[bit]);
	}

	void AccomodateEntity(uint32_t id){
		if (masks.size() <= id){
			masks.resize(id + 1);
			entityVersion.resize(id + 1);

			for (BlockAllocator * pool : components){
				if (pool)
					pool->expand(id + 1);
			}
		}
	}

	ComponentMask componentMask(const EntityId &id) {
		return masks.at(id.index);
	}

	template <typename T>
	ComponentMask componentMask() {
		ComponentMask mask;
		mask.set(T::bit());
		return mask;
	}

	template <typename T, typename T1, typename... Ts>
	ComponentMask componentMask() {
		return componentMask<T>() | componentMask<T1, Ts...>();
	}

	uint32_t index;
	std::vector<ComponentMask> masks;
	std::vector<BlockAllocator*> components;
	std::vector<uint32_t> entityVersion;
	std::list<uint32_t> freeList;
};

#include "../engine/Entity.h"

template <typename T>
typename EntityFactory::ViewIterator<T>::self_type&
EntityFactory::ViewIterator<T>::operator++(){
    index++;
    next();
    return *static_cast<T*>(this);
}

template <typename T>
bool EntityFactory::ViewIterator<T>::operator==(const T & rhs) const {
    return rhs.index == index;
};

template <typename T>
bool EntityFactory::ViewIterator<T>::operator!=(const T & rhs) const {
    return rhs.index != index;
};

template <typename T>
typename EntityFactory::ViewIterator<T>::value_type
EntityFactory::ViewIterator<T>::operator*(){
    return Entity(ef->createId(index), ef);
}

template <typename T>
const typename EntityFactory::ViewIterator<T>::value_type
EntityFactory::ViewIterator<T>::operator*() const {
    return Entity(ef->createId(index), ef);
}

template <typename T>
EntityFactory::ViewIterator<T>::ViewIterator(EntityFactory* ef,
                                             const ComponentMask mask,
                                             uint32_t index)
    : ef(ef), mask(mask), index(index), capacity(ef->capacity()) {
    ef->freeList.sort();
    freeIterator = ef->freeList.begin();
};

template <typename T>
void EntityFactory::ViewIterator<T>::next() {
    while (index < capacity && !condition())
        ++index;
};

template <typename T>
inline bool EntityFactory::ViewIterator<T>::condition() {
    return (valid()) && (ef->masks[index] & mask) == mask;
};

template <typename T>
inline bool EntityFactory::ViewIterator<T>::valid() {
    if (freeIterator != ef->freeList.end() && *freeIterator == index) {
        ++freeIterator;
        return false;
    }
    return true;
};

#endif
