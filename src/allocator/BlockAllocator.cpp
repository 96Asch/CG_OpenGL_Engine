#include "BlockAllocator.h"

size_t BlockAllocator::getSize() const {
    return size;
}

size_t BlockAllocator::getChunks() const {
    return blocks.size();
}

size_t BlockAllocator::getCapacity() const {
    return capacity;
}

void BlockAllocator::expand(const size_t &n){
	if (n >= size) {
		if (n >= capacity)
			reserve(n);
		size = n;
	}
}

void BlockAllocator::reserve(const size_t &n){
	while (capacity < n) {
		char *chunk = new char[elementSize * chunckSize];
		blocks.push_back(chunk);
		capacity += chunckSize;
	}
}

void * BlockAllocator::get(const size_t &n){
	assert(n < size);
	return blocks[n / chunckSize] + (n % chunckSize) * elementSize;
}

void * BlockAllocator::get(const size_t &n) const{
	assert(n < size);
	return blocks[n / chunckSize] + (n % chunckSize) * elementSize;
}

BlockAllocator::~BlockAllocator() {
	for (char *ptr : blocks) {
		delete[] ptr;
	}
}
