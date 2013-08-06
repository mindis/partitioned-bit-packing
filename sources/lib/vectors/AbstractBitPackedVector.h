#ifndef ABSTRACT_VECTOR_H_
#define ABSTRACT_VECTOR_H_

#include "win_defines.h"
#include <string>

class AbstractBitPackedVector {
public:
	std::string class_name;
	virtual void push_back(const uint) = 0;
	virtual uint get(const size_t) = 0;
	virtual size_t size() = 0;
	virtual void setEncodingBits(uint bits) = 0;
};

#endif