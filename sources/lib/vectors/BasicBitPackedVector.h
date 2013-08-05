#ifndef BASIC_BIT_PACKED_VECTOR
#define BASIC_BIT_PACKED_VECTOR

#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include "utils/utils.h"
#include "vectors/AbstractVector.h"


// 32 bit size
typedef uint store_t;
typedef uint value_t;


class BasicBitPackedVector : public AbstractVector {
private:


	std::vector<store_t> m_bitVectors;
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

	inline uint64_t size() {
		return m_size;
	}
	inline uint bits() {
		return m_bits;
	}


	void printConfig();
	void printBits();

	void setEncodingBits(uint bits);

	void push_back(value_t value);
	value_t get(const size_t index);

	std::vector<store_t>& vectors();

	value_t operator[] (uint const& index) const;
};



class DynamicBasicBitPackedVector : public AbstractVector {
public:
	BasicBitPackedVector* m_vector;
	uint m_bits;

	DynamicBasicBitPackedVector(uint bits);

	void setEncodingBits(uint bits);


	inline value_t get(size_t index)  {
		return m_vector->get(index);
	}
	inline void push_back(value_t value) {
		m_vector->push_back(value);
	}
	inline size_t size() {
		return m_vector->size();
	}
};



#endif