#ifndef BASIC_BIT_PACKED_VECTOR_H_
#define BASIC_BIT_PACKED_VECTOR_H_

#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include "vectors/AbstractBitPackedVector.h"
#include "utils/utils.h"


// 32 bit size
typedef uint store_t;
typedef uint value_t;


class BasicBitPackedVector : public AbstractBitPackedVector {
private:
    std::vector<store_t> m_store;
    uint m_bitOffset;

    // Bits used for each element stored in this Vector
    // Set initially, never changed
    uint m_bits;

    // Currently inserted number of values
    uint m_size;

    uint m_bvBits, m_bvShift;


public:
    BasicBitPackedVector(uint bits);
    ~BasicBitPackedVector();

    void init(uint bits);

    void push_back(const value_t value);

    value_t get(const size_t index);

    void setEncodingBits(uint bits);

    value_t operator[] (uint const& index) const;

    void printConfig();

    void printBits();

    inline size_t size() {
        return m_size;
    }

    inline uint bits() {
        return m_bits;
    }

    inline std::vector<store_t>& store() {
        return m_store;
    }
};




#endif