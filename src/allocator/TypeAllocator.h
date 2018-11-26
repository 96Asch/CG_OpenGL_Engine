#ifndef TYPEALLOCATOR_H_
#define TYPEALLOCATOR_H_

#include "BlockAllocator.h"

template <typename T>
class TypeAllocator : public BlockAllocator {

public:

    TypeAllocator();

    virtual ~TypeAllocator();

    virtual void destroy(const std::size_t &n) override;

};

template <typename T>
TypeAllocator<T>::TypeAllocator() : BlockAllocator(sizeof(T)) {};

template <typename T>
TypeAllocator<T>::~TypeAllocator() {};

template <typename T>
void TypeAllocator<T>::destroy(const std::size_t &n) {
    T *ptr = static_cast<T*>(get(n));
    ptr->~T();
};



#endif
