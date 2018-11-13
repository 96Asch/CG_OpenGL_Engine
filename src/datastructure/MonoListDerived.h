#ifndef MONOLISTDERIVED_H_
#define MONOLISTDERIVED_H_

#include <vector>
#include <algorithm>
#include "MonoListBase.h"

template <class Derived, class Base>
class MonoListDerived : public MonoListBase<Base> {

public:

private:

    std::vector<Derived> list;

    virtual void insert_(const Base &base) override;

    virtual void remove_(const Base &base) override;

    virtual void remove_(const unsigned &index, Base &base) override;

    virtual char* begin_() override;

    virtual const char* begin_() const override;

    virtual size_t size_() const override;

    virtual size_t elementSize_() const override;
};

template <class Derived, class Base>
void MonoListDerived<Derived, Base>::insert_(const Base &base) {
    list.push_back(static_cast<const Derived&>(base));
};

template <class Derived, class Base>
void MonoListDerived<Derived, Base>::remove_(const Base &base) {
    list.erase(std::remove(list.begin(), list.end(), base));
};

template <class Derived, class Base>
void MonoListDerived<Derived, Base>::remove_(const unsigned &index, Base &base) {
    if(0 < index && index < list.size()) {
        base = list[index];
        list.erase(list.begin() + index);
    }
};

template <class Derived, class Base>
char* MonoListDerived<Derived, Base>::begin_() {
    return reinterpret_cast<const char *>(
        static_cast<Base>(const_cast<Derived *>(list.data())));
};

template <class Derived, class Base>
const char* MonoListDerived<Derived, Base>::begin_() const {
    return reinterpret_cast<const char *>(
        static_cast<const Base*>(list.data()));
};

template <class Derived, class Base>
size_t MonoListDerived<Derived, Base>::size_() const {
    return list.size();
}

template <class Derived, class Base>
size_t MonoListDerived<Derived, Base>::elementSize_() const {
    return sizeof(Derived);
}

#endif
