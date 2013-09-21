#ifndef BASIC_PARTITIONED_VECTOR_H_
#define BASIC_PARTITIONED_VECTOR_H_

#include <stdexcept>
#include <algorithm>
#include "vectors/BasicBitPackedVector.h"


class BasicPartitionedVector : public AbstractBitPackedVector {
protected:
    std::vector<BasicBitPackedVector*> m_vectorPool;
    std::vector<BasicBitPackedVector*> m_vectors;
    std::vector<size_t> m_prefixSums;

    BasicBitPackedVector* m_activeVector;
    uint m_size, m_bits;

    void initializeFirstPartition(uint baseEncoding);

public:
    BasicPartitionedVector();
    BasicPartitionedVector(uint baseEncoding);
    ~BasicPartitionedVector();

    void push_back(const uint value);

    uint get(size_t index);
    uint get(uint bits, uint index);

    size_t size();
    size_t size(uint bits);

    void setEncodingBits(uint bits);

    std::vector<BasicBitPackedVector*>& vectors();
};


#endif