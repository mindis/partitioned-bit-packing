
#include "vectors/PartitionedVectorTemplate.h"
#include <stdexcept>
#include <algorithm>



template<typename _BCV>
PartitionedVectorTemplate<_BCV>::PartitionedVectorTemplate() : m_size(0) {
    initializeFirstPartition(1);
}



template<typename _BCV>
PartitionedVectorTemplate<_BCV>::PartitionedVectorTemplate(uint baseEncoding) : m_size(0) {
    initializeFirstPartition(baseEncoding);
}



template<typename _BCV>
PartitionedVectorTemplate<_BCV>::~PartitionedVectorTemplate() {
    for (uint n = 0; n < m_vectorPool.size(); ++n) {
        if (m_vectorPool[n] != NULL) delete m_vectorPool[n];
    }
}



template<typename _BCV>
void PartitionedVectorTemplate<_BCV>::setEncodingBits(uint bits) {
    if (bits > m_bits) {
        m_activeVector = m_vectorPool[bits];
        m_vectors.push_back(m_vectorPool[bits]);
        m_prefixSums.push_back(m_prefixSums.back());
        m_bits = bits;
    }
}



template<typename _BCV>
void PartitionedVectorTemplate<_BCV>::push_back(const uint value) {
    m_activeVector->push_back(value);
    m_prefixSums.back()++;
}



template<typename _BCV>
uint PartitionedVectorTemplate<_BCV>::get(size_t index) {
    // Get implementation from Get_3
    uint n = m_vectors.size() - 1;
    uint localIndex = index - m_prefixSums[n];

    for (; index < m_prefixSums[n]; --n) {
        localIndex = index - m_prefixSums[n-1];
    }

    return m_vectors[n]->get(localIndex);
}



template<typename _BCV>
uint PartitionedVectorTemplate<_BCV>::get(uint bits, uint index) {
    return m_vectors[bits]->get(index);
}



template<typename _BCV>
size_t PartitionedVectorTemplate<_BCV>::size() {
    return m_prefixSums.back();
}



template<typename _BCV>
size_t PartitionedVectorTemplate<_BCV>::size(uint bits) {
    return m_vectors[bits]->size();
}



template<typename _BCV>
std::vector<_BCV*>& PartitionedVectorTemplate<_BCV>::vectors() {
    return m_vectors;
}

template<typename _BCV>
uint PartitionedVectorTemplate<_BCV>::baseEncoding() {
    return m_baseEncoding;
}



template<typename _BCV>
void PartitionedVectorTemplate<_BCV>::initializeFirstPartition(uint baseEncoding) {
    if (baseEncoding < 1) {
        baseEncoding = 1;
        printf("BaseEncoding can't be less than 1 (%u)! It has been automatically set to 1.\n", baseEncoding);
    }
    m_baseEncoding = baseEncoding;
    m_bits = baseEncoding;

    m_vectorPool.reserve(32);
    m_vectorPool.push_back(NULL);
    for (uint n = 1; n < 32; ++n) m_vectorPool.push_back(new _BCV(n));

    m_vectors.reserve(32);
    m_prefixSums.reserve(32);

    m_activeVector = m_vectorPool[baseEncoding];
    m_vectors.push_back(m_activeVector);
    m_prefixSums.push_back(0);
    m_prefixSums.push_back(0);
}