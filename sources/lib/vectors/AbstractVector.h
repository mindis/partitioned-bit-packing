#ifndef ABSTRACT_VECTOR_H_
#define ABSTRACT_VECTOR_H_

#include <stdlib.h>
#include "os_defines.h"

class AbstractVector {
public:
	virtual ~AbstractVector() {}
    virtual void push_back(const uint) = 0;
    virtual uint get(size_t) = 0;
    virtual size_t size() = 0;
};

#endif