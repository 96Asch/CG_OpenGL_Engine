#ifndef BLOCKALLOCATOR_H_
#define BLOCKALLOCATOR_H_


#include <vector>
#include <cassert>
class BlockAllocator {

public:

	explicit BlockAllocator(std::size_t elementSize,
                            std::size_t chunckSize = 8192)
                            : elementSize(elementSize),
                              chunckSize(chunckSize),
                              size(0),
                              capacity(0) {};

    virtual ~BlockAllocator();

	size_t getSize() const;

    size_t getChunks() const;

    size_t getCapacity() const;

	void expand(const size_t &n);

    void reserve(const size_t &n);

    void *get(const size_t &n);

    void *get(const size_t &n) const;

    virtual void destroy(const size_t &n) = 0;

protected:

    std::vector<char *> blocks;
    size_t elementSize;
	size_t chunckSize;
	size_t size;
	size_t capacity;

};

#endif
