#ifndef PARTITIONED_BIT_VECTORS
#define PARTITIONED_BIT_VECTORS

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

    void initializeFirstPartition(uint baseEncoding) {
        if (baseEncoding < 1) printf("Stupid! BaseEncoding can't be less than 1!!!");
        m_bits = baseEncoding;

        m_vectorPool.reserve(32);
        m_vectorPool.push_back(NULL);
        for (uint n = 1; n < 32; ++n) m_vectorPool.push_back(new BasicBitPackedVector(n));

        m_vectors.reserve(32);
        m_prefixSums.reserve(32);

        m_activeVector = m_vectorPool[baseEncoding];
        m_vectors.push_back(m_activeVector);
        m_prefixSums.push_back(0);
        m_prefixSums.push_back(0);

    }

public:
    BasicPartitionedVector() : m_size(0) {
        initializeFirstPartition(1);
    }
    BasicPartitionedVector(uint baseEncoding) : m_size(0) {
        initializeFirstPartition(baseEncoding);
    }
    ~BasicPartitionedVector() {
        for (uint n = 0; n < m_vectorPool.size(); ++n) {
            if (m_vectorPool[n] != NULL) delete m_vectorPool[n];
        }
    }

    void setEncodingBits(uint bits) {
        if (bits > m_bits) {
            m_activeVector = m_vectorPool[bits];
            m_vectors.push_back(m_vectorPool[bits]);
            m_prefixSums.push_back(m_prefixSums.back());
            m_bits = bits;
            //printf("New Partition (Should: %u, Has: %u)\n", m_activeVector->bits(), m_activeVector->bits());
        }
    }

    void push_back(const uint value) {
        m_activeVector->push_back(value);
        m_prefixSums.back()++;
    }


    uint get(size_t index) {
        for (auto it = m_vectors.begin(); it != m_vectors.end(); ++it) {
            if (index < (*it)->size()) {
                return (*it)->get(index);
            } else {
                index -= (*it)->size();
            }
        }
        throw std::out_of_range("Index out of Bounds!");
        return 0;
    }

    uint get(uint bits, uint index) {
        return m_vectors[bits]->get(index);
    }

    size_t size() {
        return m_prefixSums.back();
    }
    size_t size(uint bits) {
        return m_vectors[bits]->size();
    }

    std::vector<BasicBitPackedVector*>& vectors() {
        return m_vectors;
    }



    void printBits() {
        for (auto it = m_vectors.begin(); it != m_vectors.end(); ++it) {
            if ((*it) != NULL && (*it)->size() > 0) {
                printf("\nVector %u Bits (size: %lu)\n", (*it)->bits(), (*it)->size());
                (*it)->printBits();
            }
        }
    }
};




class BasicPartitionedVector_PS1 : public BasicPartitionedVector {
public:
    BasicPartitionedVector_PS1() : BasicPartitionedVector() {}
    BasicPartitionedVector_PS1(uint baseEncoding) : BasicPartitionedVector(baseEncoding) {}


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


class BasicPartitionedVector_PS2 : public BasicPartitionedVector {
public:
    BasicPartitionedVector_PS2() : BasicPartitionedVector() {}
    BasicPartitionedVector_PS2(uint baseEncoding) : BasicPartitionedVector(baseEncoding) {}

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


class BasicPartitionedVector_PS3 : public BasicPartitionedVector {
public:
    BasicPartitionedVector_PS3() : BasicPartitionedVector() {}
    BasicPartitionedVector_PS3(uint baseEncoding) : BasicPartitionedVector(baseEncoding) {}

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

class BasicPartitionedVector_BitShift : public BasicPartitionedVector {
public:
    BasicPartitionedVector_BitShift() : BasicPartitionedVector() {}
    BasicPartitionedVector_BitShift(uint baseEncoding) : BasicPartitionedVector(baseEncoding) {}

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



typedef	BasicPartitionedVector_PS3	PartitionedBitPackedVector;


#endif