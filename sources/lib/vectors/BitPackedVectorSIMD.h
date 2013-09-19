#ifndef BIT_PACKED_VECTOR_SIMD_H_
#define BIT_PACKED_VECTOR_SIMD_H_


#ifdef WITH_BCV



#include "bcv/bcv.h"
#include "vectors/AbstractBitPackedVector.h"

template<uint64_t _BITS>
class BitCompressedVectorAdapter : public AbstractBitPackedVector {
private:
	BitCompressedVector<uint, _BITS> m_vector;

public:
	BitCompressedVectorAdapter() {}
	~BitCompressedVectorAdapter() {}


	void push_back(const uint val) {
		m_vector.push_back(val);
	}

	uint get(size_t index) {
		return m_vector.get(index);
	}

	size_t size() {
		return m_vector.size();
	}
	
	void setEncodingBits(uint bits) {}
};






#endif


/*

class BitPackedVectorSIMD : public AbstractBitPackedVector {
public:
	AbstractVector* m_vector;
	uint m_bits;

	void push_back(uint val) {
		m_vector->push_back(val);
	}

	uint get(const size_t index) {
		return m_vector->get(index);
	}

	uint64_t size() {
		return m_vector->size();
	}

	void setEncodingBits(uint bits) {}
	void printBits() {}
	uint bits() {
		return m_bits;
	}

	GrundVector(const uint bits) : m_bits(bits) {
		class_name = "GrundVectorAdapter";
		switch (bits) {
		case 1:
			m_vector = new BitCompressedVector<uint, 1>();
			break;
		case 2:
			m_vector = new BitCompressedVector<uint, 2>();
			break;
		case 3:
			m_vector = new BitCompressedVector<uint, 3>();
			break;
		case 4:
			m_vector = new BitCompressedVector<uint, 4>();
			break;
		case 5:
			m_vector = new BitCompressedVector<uint, 5>();
			break;
		case 6:
			m_vector = new BitCompressedVector<uint, 6>();
			break;
		case 7:
			m_vector = new BitCompressedVector<uint, 7>();
			break;
		case 8:
			m_vector = new BitCompressedVector<uint, 8>();
			break;
		case 9:
			m_vector = new BitCompressedVector<uint, 9>();
			break;
		case 10:
			m_vector = new BitCompressedVector<uint, 10>();
			break;
		case 11:
			m_vector = new BitCompressedVector<uint, 11>();
			break;
		case 12:
			m_vector = new BitCompressedVector<uint, 12>();
			break;
		case 13:
			m_vector = new BitCompressedVector<uint, 13>();
			break;
		case 14:
			m_vector = new BitCompressedVector<uint, 14>();
			break;
		case 15:
			m_vector = new BitCompressedVector<uint, 15>();
			break;
		case 16:
			m_vector = new BitCompressedVector<uint, 16>();
			break;
		case 17:
			m_vector = new BitCompressedVector<uint, 17>();
			break;
		case 18:
			m_vector = new BitCompressedVector<uint, 18>();
			break;
		case 19:
			m_vector = new BitCompressedVector<uint, 19>();
			break;
		case 20:
			m_vector = new BitCompressedVector<uint, 20>();
			break;
		case 21:
			m_vector = new BitCompressedVector<uint, 21>();
			break;
		case 22:
			m_vector = new BitCompressedVector<uint, 22>();
			break;
		case 23:
			m_vector = new BitCompressedVector<uint, 23>();
			break;
		case 24:
			m_vector = new BitCompressedVector<uint, 24>();
			break;
		case 25:
			m_vector = new BitCompressedVector<uint, 25>();
			break;
		case 26:
			m_vector = new BitCompressedVector<uint, 26>();
			break;
		case 27:
			m_vector = new BitCompressedVector<uint, 27>();
			break;
		case 28:
			m_vector = new BitCompressedVector<uint, 28>();
			break;
		case 29:
			m_vector = new BitCompressedVector<uint, 29>();
			break;
		case 30:
			m_vector = new BitCompressedVector<uint, 30>();
			break;
		case 31:
			m_vector = new BitCompressedVector<uint, 31>();
			break;
		case 32:
			m_vector = new BitCompressedVector<uint, 32>();
			break;
		case 33:
			m_vector = new BitCompressedVector<uint, 33>();
			break;
		case 34:
			m_vector = new BitCompressedVector<uint, 34>();
			break;
		case 35:
			m_vector = new BitCompressedVector<uint, 35>();
			break;
		case 36:
			m_vector = new BitCompressedVector<uint, 36>();
			break;
		case 37:
			m_vector = new BitCompressedVector<uint, 37>();
			break;
		case 38:
			m_vector = new BitCompressedVector<uint, 38>();
			break;
		case 39:
			m_vector = new BitCompressedVector<uint, 39>();
			break;
		case 40:
			m_vector = new BitCompressedVector<uint, 40>();
			break;
		case 41:
			m_vector = new BitCompressedVector<uint, 41>();
			break;
		case 42:
			m_vector = new BitCompressedVector<uint, 42>();
			break;
		case 43:
			m_vector = new BitCompressedVector<uint, 43>();
			break;
		case 44:
			m_vector = new BitCompressedVector<uint, 44>();
			break;
		case 45:
			m_vector = new BitCompressedVector<uint, 45>();
			break;
		case 46:
			m_vector = new BitCompressedVector<uint, 46>();
			break;
		case 47:
			m_vector = new BitCompressedVector<uint, 47>();
			break;
		case 48:
			m_vector = new BitCompressedVector<uint, 48>();
			break;
		case 49:
			m_vector = new BitCompressedVector<uint, 49>();
			break;
		case 50:
			m_vector = new BitCompressedVector<uint, 50>();
			break;
		case 51:
			m_vector = new BitCompressedVector<uint, 51>();
			break;
		case 52:
			m_vector = new BitCompressedVector<uint, 52>();
			break;
		case 53:
			m_vector = new BitCompressedVector<uint, 53>();
			break;
		case 54:
			m_vector = new BitCompressedVector<uint, 54>();
			break;
		case 55:
			m_vector = new BitCompressedVector<uint, 55>();
			break;
		case 56:
			m_vector = new BitCompressedVector<uint, 56>();
			break;
		case 57:
			m_vector = new BitCompressedVector<uint, 57>();
			break;
		case 58:
			m_vector = new BitCompressedVector<uint, 58>();
			break;
		case 59:
			m_vector = new BitCompressedVector<uint, 59>();
			break;
		case 60:
			m_vector = new BitCompressedVector<uint, 60>();
			break;
		case 61:
			m_vector = new BitCompressedVector<uint, 61>();
			break;
		case 62:
			m_vector = new BitCompressedVector<uint, 62>();
			break;
		case 63:
			m_vector = new BitCompressedVector<uint, 63>();
			break;
		case 64:
			m_vector = new BitCompressedVector<uint, 64>();
			break;
		default:
			printf("GrundVectorAdapter not specified!");
		}
	}

	~GrundVector() {
		delete m_vector;
	}
};
*/

#endif

