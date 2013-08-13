#ifndef PARTITIONED_BIT_PACKED_VECTORS_H_
#define PARTITIONED_BIT_PACKED_VECTORS_H_

#include "vectors/BasicPartitionedVector.h"



/**
 * @brief Get-implementation using the prefix-sum.
 */
class PartitionedBitPackedVector_Get_1 : public BasicPartitionedVector {
public:
    PartitionedBitPackedVector_Get_1() : BasicPartitionedVector() {}
    PartitionedBitPackedVector_Get_1(uint baseEncoding) : BasicPartitionedVector(baseEncoding) {}

    uint get(size_t globalIndex) {
        for (uint n = 0; n < m_vectors.size(); ++n) {
            uint localIndex = globalIndex - m_prefixSums[n];
            if (globalIndex < m_prefixSums[n+1])
                return m_vectors[n]->get(localIndex);
        }
        throw std::out_of_range("Index out of Bounds!");
        return 0;
    }
};



/**
 * @brief Get-implementation using the prefix-sum starting from back.
 */
class PartitionedBitPackedVector_Get_2 : public BasicPartitionedVector {
public:
    PartitionedBitPackedVector_Get_2() : BasicPartitionedVector() {}
    PartitionedBitPackedVector_Get_2(uint baseEncoding) : BasicPartitionedVector(baseEncoding) {}

    uint get(size_t globalIndex) {
        for (uint n = m_vectors.size() - 1; n >= 0; --n) {
            uint localIndex = globalIndex - m_prefixSums[n];
            if (globalIndex >= m_prefixSums[n])
                return m_vectors[n]->get(localIndex);
        }
        throw std::out_of_range("Index out of Bounds!");
        return 0;
    }
};



/**
 * @brief Get-implementation using the prefix-sum starting from back with a single loop and no inner branches.
 */
class PartitionedBitPackedVector_Get_3 : public BasicPartitionedVector {
public:
    PartitionedBitPackedVector_Get_3() : BasicPartitionedVector() {}
    PartitionedBitPackedVector_Get_3(uint baseEncoding) : BasicPartitionedVector(baseEncoding) {}

    uint get(size_t globalIndex) {
        uint n = m_vectors.size() - 1;
        uint localIndex = globalIndex - m_prefixSums[n];

        for (; globalIndex < m_prefixSums[n]; --n) {
            localIndex = globalIndex - m_prefixSums[n-1];
        }

        return m_vectors[n]->get(localIndex);
    }

};





#ifdef __GNUC__
/**
 * @brief Get-implementation using bitshifts and popcnt.
 */
class PartitionedBitPackedVector_popcnt : public BasicPartitionedVector {
public:
    PartitionedBitPackedVector_BitShift() : BasicPartitionedVector() {}
    PartitionedBitPackedVector_BitShift(uint baseEncoding) : BasicPartitionedVector(baseEncoding) {}

    uint get(size_t globalIndex) {
        // Bitmap Implementation
        unsigned long bitmap1 = 0, bitmap2 = 0, bitmap3 = 0, bitmap4 = 0;

        bitmap1 |= ((globalIndex - m_prefixSums[0]) >> 63L) << 0L;
        bitmap2 |= ((globalIndex - m_prefixSums[1]) >> 63L) << 1L;
        bitmap3 |= ((globalIndex - m_prefixSums[2]) >> 63L) << 2L;
        bitmap4 |= ((globalIndex - m_prefixSums[3]) >> 63L) << 3L;
        bitmap1 |= ((globalIndex - m_prefixSums[4]) >> 63L) << 4L;
        bitmap2 |= ((globalIndex - m_prefixSums[5]) >> 63L) << 5L;
        bitmap3 |= ((globalIndex - m_prefixSums[6]) >> 63L) << 6L;
        bitmap4 |= ((globalIndex - m_prefixSums[7]) >> 63L) << 7L;
        bitmap1 |= ((globalIndex - m_prefixSums[8]) >> 63L) << 8L;
        bitmap2 |= ((globalIndex - m_prefixSums[9]) >> 63L) << 9L;

        unsigned long vecIndex = 10 - __builtin_popcount(bitmap1 | bitmap2 | bitmap3 | bitmap4) - 1;
        return m_vectors[vecIndex]->get(globalIndex - m_prefixSums[vecIndex]);


        // Addition
        /*
        uint locals[32];
        uint vecIndex[2] = {0};

        for (uint n = 0; n < 16; ++n) {
        locals[n] = globalIndex - m_prefixSums[n];
        vecIndex[n & 1] += locals[n] >> 31L;
        }
        locals[0] = globalIndex - m_prefixSums[0]; vecIndex[0] += (uint)(globalIndex - m_prefixSums[0]) >> 31L;
        locals[1] = globalIndex - m_prefixSums[1]; vecIndex[1] += (uint)(globalIndex - m_prefixSums[1]) >> 31L;
        locals[2] = globalIndex - m_prefixSums[2]; vecIndex[0] += (uint)(globalIndex - m_prefixSums[2]) >> 31L;
        locals[3] = globalIndex - m_prefixSums[3]; vecIndex[1] += (uint)(globalIndex - m_prefixSums[3]) >> 31L;
        locals[4] = globalIndex - m_prefixSums[4]; vecIndex[0] += (uint)(globalIndex - m_prefixSums[4]) >> 31L;
        locals[5] = globalIndex - m_prefixSums[5]; vecIndex[1] += (uint)(globalIndex - m_prefixSums[5]) >> 31L;
        locals[6] = globalIndex - m_prefixSums[6]; vecIndex[0] += (uint)(globalIndex - m_prefixSums[6]) >> 31L;
        locals[7] = globalIndex - m_prefixSums[7]; vecIndex[1] += (uint)(globalIndex - m_prefixSums[7]) >> 31L;
        locals[8] = globalIndex - m_prefixSums[8]; vecIndex[0] += (uint)(globalIndex - m_prefixSums[8]) >> 31L;
        locals[9] = globalIndex - m_prefixSums[9]; vecIndex[1] += (uint)(globalIndex - m_prefixSums[9]) >> 31L;
        locals[10] = globalIndex - m_prefixSums[10]; vecIndex[0] += (uint)(globalIndex - m_prefixSums[10]) >> 31L;
        locals[11] = globalIndex - m_prefixSums[11]; vecIndex[1] += (uint)(globalIndex - m_prefixSums[11]) >> 31L;
        locals[12] = globalIndex - m_prefixSums[12]; vecIndex[0] += (uint)(globalIndex - m_prefixSums[12]) >> 31L;
        locals[13] = globalIndex - m_prefixSums[13]; vecIndex[1] += (uint)(globalIndex - m_prefixSums[13]) >> 31L;
        locals[14] = globalIndex - m_prefixSums[14]; vecIndex[0] += (uint)(globalIndex - m_prefixSums[14]) >> 31L;
        locals[15] = globalIndex - m_prefixSums[15]; vecIndex[1] += (uint)(globalIndex - m_prefixSums[15]) >> 31L;

        vecIndex[0] = 16 - 1 - vecIndex[0] - vecIndex[1];
        return m_vectors[vecIndex[0]]->get(locals[vecIndex[0]]);
        //*/
    }
};
#endif

#endif