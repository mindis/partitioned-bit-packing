#ifndef ABSTRACT_BIT_PACKED_VECTOR_H_
#define ABSTRACT_BIT_PACKED_VECTOR_H_

#include "win_defines.h"

class AbstractBitPackedVector {
public:
    virtual void push_back(const uint) = 0;
    virtual uint get(const size_t) = 0;
    virtual size_t size() = 0;
    virtual void setEncodingBits(uint bits) = 0;
};

#endif