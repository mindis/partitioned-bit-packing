#ifndef PARTITIONED_VECTOR_TEMPLATE_H_
#define PARTITIONED_VECTOR_TEMPLATE_H_

#include <vector>
#include "vectors/AbstractBitPackedVector.h"

template<typename _BPV>
class PartitionedVectorTemplate : public AbstractBitPackedVector {
protected:
    std::vector<_BPV*> m_vectorPool;
    std::vector<_BPV*> m_vectors;
    std::vector<size_t> m_prefixSums;

    _BPV* m_activeVector;
    uint m_size, m_bits, m_baseEncoding;

    void initializeFirstPartition(uint baseEncoding);

public:
    PartitionedVectorTemplate();
    PartitionedVectorTemplate(uint baseEncoding);
    ~PartitionedVectorTemplate();

    void push_back(const uint value);

    uint get(size_t index);
    uint get(uint bits, uint index);

    size_t size();
    size_t size(uint bits);

    void setEncodingBits(uint bits);

    uint baseEncoding();

    std::vector<_BPV*>& vectors();
};


// Due to linking errors int the compiler
// the implementations need to be included by every file
// that wants to use this template class
#include "PartitionedVectorTemplate.cpp"


#endif