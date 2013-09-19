
#include "vectors/BasicPartitionedVector.h"

BasicPartitionedVector::BasicPartitionedVector() : m_size(0) {
    initializeFirstPartition(1);
}

BasicPartitionedVector::BasicPartitionedVector(uint baseEncoding) : m_size(0) {
    initializeFirstPartition(baseEncoding);
}

BasicPartitionedVector::~BasicPartitionedVector() {
    for (uint n = 0; n < m_vectorPool.size(); ++n) {
        if (m_vectorPool[n] != NULL) delete m_vectorPool[n];
    }
}

void BasicPartitionedVector::setEncodingBits(uint bits) {
    if (bits > m_bits) {
        m_activeVector = m_vectorPool[bits];
        m_vectors.push_back(m_vectorPool[bits]);
        m_prefixSums.push_back(m_prefixSums.back());
        m_bits = bits;
    }
}

void BasicPartitionedVector::push_back(const uint value) {
    m_activeVector->push_back(value);
    m_prefixSums.back()++;
}

uint BasicPartitionedVector::get(size_t index) {
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

uint BasicPartitionedVector::get(uint bits, uint index) {
    return m_vectors[bits]->get(index);
}

size_t BasicPartitionedVector::size() {
    return m_prefixSums.back();
}

size_t BasicPartitionedVector::size(uint bits) {
    return m_vectors[bits]->size();
}

std::vector<BasicBitPackedVector*>& BasicPartitionedVector::vectors() {
    return m_vectors;
}

void BasicPartitionedVector::initializeFirstPartition(uint baseEncoding) {
    if (baseEncoding < 1) {
        baseEncoding = 1;
        printf("BaseEncoding can't be less than 1 (%u)! It has been automatically set to 1.\n", baseEncoding);
    }
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