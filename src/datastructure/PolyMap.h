#ifndef POLYMAP_H_
#define POLYMAP_H_

#include <memory>
#include <type_traits>
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
    F for_each(F f);

    template <typename F>
    F for_each(F f) const;

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
F PolyMap<Base>::for_each(F f) {
    for(const auto &pointer : polyMap)
        pointer.second->for_each(f);
    return std::move(f);
};

template <class Base>
template <typename F>
F PolyMap<Base>::for_each(F f) const {
    for(const auto &pointer : polyMap)
        const_cast<const List&>(pointer->second).for_each(f);
    return std::move(f);
};


#endif
