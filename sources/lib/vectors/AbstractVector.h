#ifndef ABSTRACT_VECTOR
#define ABSTRACT_VECTOR

#include <string>

class AbstractVector {
public:
	std::string class_name;
	virtual void push_back(const uint) = 0;
	virtual uint get(const size_t) = 0;
	virtual uint64_t size() = 0;
	virtual void setEncodingBits(uint bits) = 0;
};

#endif