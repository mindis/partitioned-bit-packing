
#include "vectors/DynamicBitPackedVector.h"

DynamicBitPackedVector::DynamicBitPackedVector(uint bits) {
	m_vector = new BasicBitPackedVector(bits);
	m_bits = bits;
}

void DynamicBitPackedVector::setEncodingBits(uint bits) {
	if (bits > m_bits) {
		BasicBitPackedVector* old_vector = m_vector;
		size_t old_size = old_vector->size();

		m_vector = new BasicBitPackedVector(bits);
		for (uint n = 0; n < old_size; ++n) {
			m_vector->push_back(old_vector->get(n));
		}

		m_bits = bits;

        // Garbage Collection turned off for benchmark purposes
		// delete old_vector;
	}
}
