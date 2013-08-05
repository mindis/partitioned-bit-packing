
#include "BasicBitPackedVector.h"

#include <bitset>


BasicBitPackedVector::BasicBitPackedVector(uint bits) {
	init(bits);
}
BasicBitPackedVector::~BasicBitPackedVector() {

}

void BasicBitPackedVector::init(uint bits) {
	m_bvBits = sizeof(store_t) * 8;
	m_bits = bits;
	m_bvShift = m_bvBits - m_bits;
	m_bitOffset = 0;
	m_size = 0;
	m_bitVectors.reserve(1024*1024);

	if (bits == 0) {
		printf("Can not initialize with 0 bit encoding.\n");
	}
	if (bits > m_bvBits) {
		printf("Too many bits.\n");
	}
}


void BasicBitPackedVector::printConfig() {
	printf("Bits: %d\nSize per element: %d\nShift: %u\n", m_bits, m_bvBits, m_bvShift);
	for (uint n = 0; n < m_size; ++n) {
		printf("Element %u: %u\n", n, get(n));
	}
}
void BasicBitPackedVector::printBits() {
	for (uint n = 0; n < m_bitVectors.size(); ++n) {
		printf("BitVector %.3u:\t%s\n", n, std::bitset<32>(m_bitVectors[n]).to_string().c_str());
	}
}


void BasicBitPackedVector::push_back(value_t value) {
	store_t element = value;
	store_t next = (element << m_bvShift);
	uint newBitOffset = (m_bitOffset + m_bits) % m_bvBits;

	// Create a new bit-vector if the current offset is 0
	if (m_bitOffset == 0) {
		m_bitVectors.push_back(next);

	} else {
		// Append the value to the last bit-vector
		store_t last = m_bitVectors.back();
		m_bitVectors.pop_back();

		last = last | (next >> m_bitOffset);
		m_bitVectors.push_back(last);


		// Create a new bit-packed if the value didn't fit entirely
		if (newBitOffset < m_bitOffset && newBitOffset != 0) {
			store_t overlap = next << (m_bits - newBitOffset);
			m_bitVectors.push_back(overlap);
		}
	}

	m_bitOffset = newBitOffset;
	m_size++;
}

void BasicBitPackedVector::setEncodingBits(uint bits) {
	/*
	if (bits > m_bits) {
		printf("Reinitializing with %u bits!\n", bits);
		BasicBitPackedVector* b = new BasicBitPackedVector(bits);
		for (size_t n = 0; n < m_size; ++n) b->push_back(this->get(n));

		this->init(bits);
		this->m_bitVectors.swap(b->vectors());
	}
	//*/
}

value_t BasicBitPackedVector::get(const size_t index) {
	return (*this)[index];
}

std::vector<store_t>& BasicBitPackedVector::vectors() {
	return m_bitVectors;
}

value_t BasicBitPackedVector::operator[](uint const& index) const {
	uint bitOffset = (index * m_bits) % m_bvBits;
	uint vectorIndex = (index * m_bits - bitOffset) / m_bvBits;

	if (bitOffset + m_bits <= m_bvBits) {
		store_t elm = m_bitVectors[vectorIndex];
		uint lShift = bitOffset,
		     rShift = m_bvBits - (bitOffset + m_bits);

		return ((elm << lShift) >> lShift >> rShift);

	} else {
		uint overlap = bitOffset + m_bits - m_bvBits;

		store_t left = m_bitVectors[vectorIndex] << bitOffset;
		store_t right = m_bitVectors[vectorIndex+1] >> (m_bvBits - overlap);

		return (left >> (m_bvBits - m_bits)) | right;
	}
	return -1;
}






DynamicBasicBitPackedVector::DynamicBasicBitPackedVector(uint bits) {
	m_vector = new BasicBitPackedVector(bits);
	m_bits = bits;
}

void DynamicBasicBitPackedVector::setEncodingBits(uint bits) {
	if (bits > m_bits) {
		BasicBitPackedVector* old_vector = m_vector;
		size_t old_size = old_vector->size();

		m_vector = new BasicBitPackedVector(bits);
		for (uint n = 0; n < old_size; ++n) {
			m_vector->push_back(old_vector->get(n));
		}

		m_bits = bits;
		//delete old_vector;
	}
}

