#ifndef POLYMAP_H_
#define POLYMAP_H_

#include <memory>
#include <type_traits>
#include <typeindex>
#include <typeinfo>
#include <map>

#include "MonoListBase.h"
#include "MonoListDerived.h"

template <class Base>
class PolyMap {

public:

    template <class Derived>
    void insert(const Derived& derived,
                typename std::enable_if<
                    std::is_base_of<
                        Base, Derived>::value>::type* =  0);

    template <class Derived>
    void remove(const Derived& derived,
                typename std::enable_if<
                    std::is_base_of<
                        Base, Derived>::value>::type* =  0);

    template <typename F>
    void remove_if(F &&func, Base &base);

    template <typename F>
    F for_each(F &&func);

    template <typename F>
    F for_each(F &&func) const;

    template <class Derived>
    typename MonoListDerived<Derived, Base>::Iterator begin();

    template <class Derived>
    typename MonoListDerived<Derived, Base>::Iterator end();

    template <class Derived>
    MonoListDerived<Derived, Base>& getList();

private:

    typedef MonoListBase<Base> List;
    typedef std::unique_ptr<List> Pointer;

    std::map<std::type_index, Pointer> polyMap;
};

template <class Base>
template <class Derived>
void PolyMap<Base>::insert(const Derived& derived,
                            typename std::enable_if<
                                    std::is_base_of<
                                    Base, Derived>::value>::type*)
{
    auto &listPointer = polyMap[typeid(derived)];
    if(!listPointer)
        listPointer.reset(new MonoListDerived<Derived, Base>());
    listPointer->insert(derived);
};

template <class Base>
template <class Derived>
void PolyMap<Base>::remove(const Derived& derived,
                            typename std::enable_if<
                                std::is_base_of<
                                    Base, Derived>::value>::type*)
{
    auto &listPointer = polyMap[typeid(derived)];
    if(listPointer)
        listPointer->remove(derived);
};


template <class Base>
template <typename F>
void PolyMap<Base>::remove_if(F &&func, Base &base) {
    for(const auto &pointer : polyMap)
        pointer.second->remove_if(func, base);
}

template <class Base>
template <typename F>
F PolyMap<Base>::for_each(F &&func) {
    for(const auto &pointer : polyMap)
        pointer.second->for_each(func);
    return std::move(func);
};

template <class Base>
template <typename F>
F PolyMap<Base>::for_each(F &&func) const {
    for(const auto &pointer : polyMap)
        const_cast<const List&>(pointer->second).for_each(func);
    return std::move(func);
};

template <class Base>
template <class Derived>
typename MonoListDerived<Derived, Base>::Iterator PolyMap<Base>::begin() {
    auto &listPointer = polyMap[std::type_index(typeid(Derived))];
    return static_cast<MonoListDerived<Derived, Base>*>(listPointer.get())->begin();
}

template <class Base>
template <class Derived>
typename MonoListDerived<Derived, Base>::Iterator PolyMap<Base>::end() {
    auto &listPointer = polyMap[std::type_index(typeid(Derived))];
    return static_cast<MonoListDerived<Derived, Base>*>(listPointer.get())->end();
}

template <class Base>
template <class Derived>
MonoListDerived<Derived, Base>& PolyMap<Base>::getList() {
    auto &listPointer = polyMap[std::type_index(typeid(Derived))];
    return *(static_cast<MonoListDerived<Derived, Base>*>(listPointer.get()));
}

#endif
