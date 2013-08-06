
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
	m_store.reserve(1024*1024);

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
	for (uint n = 0; n < m_store.size(); ++n) {
		printf("BitVector %.3u:\t%s\n", n, std::bitset<32>(int(m_store[n])).to_string().c_str());
	}
}


void BasicBitPackedVector::push_back(value_t value) {
	store_t element = value;
	store_t next = (element << m_bvShift);
	uint newBitOffset = (m_bitOffset + m_bits) % m_bvBits;

	// Create a new bit-vector if the current offset is 0
	if (m_bitOffset == 0) {
		m_store.push_back(next);

	} else {
		// Append the value to the last bit-vector
		store_t last = m_store.back();
		m_store.pop_back();

		last = last | (next >> m_bitOffset);
		m_store.push_back(last);


		// Create a new bit-packed if the value didn't fit entirely
		if (newBitOffset < m_bitOffset && newBitOffset != 0) {
			store_t overlap = next << (m_bits - newBitOffset);
			m_store.push_back(overlap);
		}
	}

	m_bitOffset = newBitOffset;
	m_size++;
}

void BasicBitPackedVector::setEncodingBits(uint bits) {
}

value_t BasicBitPackedVector::get(const size_t index) {
	return (*this)[index];
}

value_t BasicBitPackedVector::operator[](uint const& index) const {
	uint bitOffset = (index * m_bits) % m_bvBits;
	uint vectorIndex = (index * m_bits - bitOffset) / m_bvBits;

	if (bitOffset + m_bits <= m_bvBits) {
		store_t elm = m_store[vectorIndex];
		uint lShift = bitOffset,
		     rShift = m_bvBits - (bitOffset + m_bits);

		return ((elm << lShift) >> lShift >> rShift);

	} else {
		uint overlap = bitOffset + m_bits - m_bvBits;

		store_t left = m_store[vectorIndex] << bitOffset;
		store_t right = m_store[vectorIndex+1] >> (m_bvBits - overlap);

		return (left >> (m_bvBits - m_bits)) | right;
	}
	return -1;
}



