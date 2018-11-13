#ifndef MONOLISTBASE_H_
#define MONOLISTBASE_H_

template<class Base>
class MonoListBase {

public:

    virtual ~MonoListBase();

    void insert(const Base &base);

    void remove(const Base &base);

    void remove(const unsigned &index, Base &base  );

    template <typename F>
    Base* get_if(F &&func);

    template <typename F>
    void remove_if(F &&func);

    template <typename F>
    void for_each(F &&func);

    template <typename F>
    void for_each(F &&func) const;

private:

    virtual void insert_(const Base &base) = 0;

    virtual void remove_(const Base &base) = 0;

    virtual void remove_(const unsigned index, Base &base) = 0;

    virtual char* begin_() = 0;

    virtual const char* begin_() const = 0;

    virtual size_t size_() const = 0;

    virtual size_t elementSize_() const = 0;
};

template <class Base>
void MonoListBase<Base>::insert(const Base &base) {
    insert_(base);
};

template <class Base>
void MonoListBase<Base>::remove(const Base &base) {
    remove_(base);
};

template <class Base>
void MonoListBase<Base>::remove(const unsigned &index, Base &base) {
    remove_(index, base);
};

template <class Base>
template <typename F>
Base* MonoListBase<Base>::get_if(F &&func) {
    std::size_t s = elementSize_();
    unsigned index = 0;
    for(auto it= begin_(), end = it + size_() * s; it != end; it += s){
        if (func(*reinterpret_cast<Base*>(it))) {
            return reinterpret_cast<Base*>(it);
        }
    }
    return nullptr;
};

template <class Base>
template <typename F>
void MonoListBase<Base>::remove_if(F &&func) {
    std::size_t s = elementSize_();
    unsigned index = 0;
    for(auto it= begin_(), end = it + size_() * s; it != end; it += s){
        if (func(*reinterpret_cast<Base*>(it))) {
            remove(index);
        }
        ++index;
    }
}

template <class Base>
template <typename F>
void MonoListBase<Base>::for_each(F &&func){
   std::size_t s = elementSize_();
   for(auto it= begin_(), end = it + size_() * s; it != end; it += s){
       func(*reinterpret_cast<Base*>(it));
   }
};

template <class Base>
template <typename F>
void MonoListBase<Base>::for_each(F &&func) const{
   std::size_t s = elementSize_();
   for(auto it= begin_(), end = it + size_() * s; it != end; it += s){
       func(*reinterpret_cast<const Base*>(it));
   }
};

#endif
