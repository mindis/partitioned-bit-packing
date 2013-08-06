#ifndef DYNAMIC_BIT_PACKED_VECTOR_H_
#define DYNAMIC_BIT_PACKED_VECTOR_H_

#include "vectors/BasicBitPackedVector.h"

class DynamicBitPackedVector : public AbstractBitPackedVector {
public:
    BasicBitPackedVector* m_vector;
    uint m_bits;

    DynamicBitPackedVector(uint bits);

    void setEncodingBits(uint bits);


    inline value_t get(const size_t index)  {
        return m_vector->get(index);
    }
    inline void push_back(const value_t value) {
        m_vector->push_back(value);
    }
    inline size_t size() {
        return m_vector->size();
    }
};




#endif