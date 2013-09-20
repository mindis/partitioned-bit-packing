#ifndef PARTITIONED_VECTOR_SIMD_H_
#define PARTITIONED_VECTOR_SIMD_H_


#ifdef WITH_BCV

#include "vectors/BitPackedVectorSIMD.h"


class PartitionedVectorSIMD : public AbstractBitPackedVector {
protected:
    std::vector<BitPackedVectorSIMD*> m_vectorPool;
    std::vector<BitPackedVectorSIMD*> m_vectors;
    std::vector<size_t> m_prefixSums;

    BitPackedVectorSIMD* m_activeVector;
    uint m_size, m_bits;

    void initializeFirstPartition(uint baseEncoding);

public:
    PartitionedVectorSIMD();
    PartitionedVectorSIMD(uint baseEncoding);
    ~PartitionedVectorSIMD();

    void push_back(const uint value);

    uint get(size_t index);
    uint get(uint bits, uint index);

    size_t size();
    size_t size(uint bits);

    void setEncodingBits(uint bits);

    std::vector<BitPackedVectorSIMD*>& vectors();
};







#endif
// WITH_BCV

#endif
// PARTITIONED_VECTOR_SIMD_H_