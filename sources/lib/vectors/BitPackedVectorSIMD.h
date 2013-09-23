#ifndef BIT_PACKED_VECTOR_SIMD_H_
#define BIT_PACKED_VECTOR_SIMD_H_

#ifdef WITH_BCV


#include <memory>
#include "bcv/bcv.h"
#include "vectors/AbstractVector.h"
#include "vectors/AbstractBitPackedVector.h"

template<uint64_t _BITS>
class BitCompressedVectorAdapter : public AbstractVector {
private:
	BitCompressedVector<uint, _BITS> m_vector;

public:
	BitCompressedVectorAdapter() {}
	~BitCompressedVectorAdapter() {}


	inline void push_back(const uint val) {
		m_vector.push_back(val);
	}

	inline uint get(size_t index) {
		return m_vector.get(index);
	}

	inline size_t size() {
		return m_vector.size();
	}
};


class BitPackedVectorSIMD : public AbstractBitPackedVector {
private:
	std::unique_ptr<AbstractVector> m_vector;
	uint m_bits;
	
public:

	inline void push_back(uint val) {
		m_vector->push_back(val);
	}

	inline uint get(const size_t index) {
		return m_vector->get(index);
	}

	inline size_t size() {
		return m_vector->size();
	}

	inline void setEncodingBits(uint bits) {}

	inline uint bits() {
		return m_bits;
	}



	~BitPackedVectorSIMD() {
	}

	BitPackedVectorSIMD(uint bits) : m_bits(bits) {
		switch (bits) {
		case 1:
			m_vector = std::unique_ptr<AbstractVector>(new BitCompressedVectorAdapter<1>());
			break;
		case 2:
			m_vector = std::unique_ptr<AbstractVector>(new BitCompressedVectorAdapter<2>());
			break;
		case 3:
			m_vector = std::unique_ptr<AbstractVector>(new BitCompressedVectorAdapter<3>());
			break;
		case 4:
			m_vector = std::unique_ptr<AbstractVector>(new BitCompressedVectorAdapter<4>());
			break;
		case 5:
			m_vector = std::unique_ptr<AbstractVector>(new BitCompressedVectorAdapter<5>());
			break;
		case 6:
			m_vector = std::unique_ptr<AbstractVector>(new BitCompressedVectorAdapter<6>());
			break;
		case 7:
			m_vector = std::unique_ptr<AbstractVector>(new BitCompressedVectorAdapter<7>());
			break;
		case 8:
			m_vector = std::unique_ptr<AbstractVector>(new BitCompressedVectorAdapter<8>());
			break;
		case 9:
			m_vector = std::unique_ptr<AbstractVector>(new BitCompressedVectorAdapter<9>());
			break;
		case 10:
			m_vector = std::unique_ptr<AbstractVector>(new BitCompressedVectorAdapter<10>());
			break;
		case 11:
			m_vector = std::unique_ptr<AbstractVector>(new BitCompressedVectorAdapter<11>());
			break;
		case 12:
			m_vector = std::unique_ptr<AbstractVector>(new BitCompressedVectorAdapter<12>());
			break;
		case 13:
			m_vector = std::unique_ptr<AbstractVector>(new BitCompressedVectorAdapter<13>());
			break;
		case 14:
			m_vector = std::unique_ptr<AbstractVector>(new BitCompressedVectorAdapter<14>());
			break;
		case 15:
			m_vector = std::unique_ptr<AbstractVector>(new BitCompressedVectorAdapter<15>());
			break;
		case 16:
			m_vector = std::unique_ptr<AbstractVector>(new BitCompressedVectorAdapter<16>());
			break;
		case 17:
			m_vector = std::unique_ptr<AbstractVector>(new BitCompressedVectorAdapter<17>());
			break;
		case 18:
			m_vector = std::unique_ptr<AbstractVector>(new BitCompressedVectorAdapter<18>());
			break;
		case 19:
			m_vector = std::unique_ptr<AbstractVector>(new BitCompressedVectorAdapter<19>());
			break;
		case 20:
			m_vector = std::unique_ptr<AbstractVector>(new BitCompressedVectorAdapter<20>());
			break;
		case 21:
			m_vector = std::unique_ptr<AbstractVector>(new BitCompressedVectorAdapter<21>());
			break;
		case 22:
			m_vector = std::unique_ptr<AbstractVector>(new BitCompressedVectorAdapter<22>());
			break;
		case 23:
			m_vector = std::unique_ptr<AbstractVector>(new BitCompressedVectorAdapter<23>());
			break;
		case 24:
			m_vector = std::unique_ptr<AbstractVector>(new BitCompressedVectorAdapter<24>());
			break;
		case 25:
			m_vector = std::unique_ptr<AbstractVector>(new BitCompressedVectorAdapter<25>());
			break;
		case 26:
			m_vector = std::unique_ptr<AbstractVector>(new BitCompressedVectorAdapter<26>());
			break;
		case 27:
			m_vector = std::unique_ptr<AbstractVector>(new BitCompressedVectorAdapter<27>());
			break;
		case 28:
			m_vector = std::unique_ptr<AbstractVector>(new BitCompressedVectorAdapter<28>());
			break;
		case 29:
			m_vector = std::unique_ptr<AbstractVector>(new BitCompressedVectorAdapter<29>());
			break;
		case 30:
			m_vector = std::unique_ptr<AbstractVector>(new BitCompressedVectorAdapter<30>());
			break;
		case 31:
			m_vector = std::unique_ptr<AbstractVector>(new BitCompressedVectorAdapter<31>());
			break;
		case 32:
			m_vector = std::unique_ptr<AbstractVector>(new BitCompressedVectorAdapter<32>());
			break;
		case 33:
			m_vector = std::unique_ptr<AbstractVector>(new BitCompressedVectorAdapter<33>());
			break;
		case 34:
			m_vector = std::unique_ptr<AbstractVector>(new BitCompressedVectorAdapter<34>());
			break;
		case 35:
			m_vector = std::unique_ptr<AbstractVector>(new BitCompressedVectorAdapter<35>());
			break;
		case 36:
			m_vector = std::unique_ptr<AbstractVector>(new BitCompressedVectorAdapter<36>());
			break;
		case 37:
			m_vector = std::unique_ptr<AbstractVector>(new BitCompressedVectorAdapter<37>());
			break;
		case 38:
			m_vector = std::unique_ptr<AbstractVector>(new BitCompressedVectorAdapter<38>());
			break;
		case 39:
			m_vector = std::unique_ptr<AbstractVector>(new BitCompressedVectorAdapter<39>());
			break;
		case 40:
			m_vector = std::unique_ptr<AbstractVector>(new BitCompressedVectorAdapter<40>());
			break;
		case 41:
			m_vector = std::unique_ptr<AbstractVector>(new BitCompressedVectorAdapter<41>());
			break;
		case 42:
			m_vector = std::unique_ptr<AbstractVector>(new BitCompressedVectorAdapter<42>());
			break;
		case 43:
			m_vector = std::unique_ptr<AbstractVector>(new BitCompressedVectorAdapter<43>());
			break;
		case 44:
			m_vector = std::unique_ptr<AbstractVector>(new BitCompressedVectorAdapter<44>());
			break;
		case 45:
			m_vector = std::unique_ptr<AbstractVector>(new BitCompressedVectorAdapter<45>());
			break;
		case 46:
			m_vector = std::unique_ptr<AbstractVector>(new BitCompressedVectorAdapter<46>());
			break;
		case 47:
			m_vector = std::unique_ptr<AbstractVector>(new BitCompressedVectorAdapter<47>());
			break;
		case 48:
			m_vector = std::unique_ptr<AbstractVector>(new BitCompressedVectorAdapter<48>());
			break;
		case 49:
			m_vector = std::unique_ptr<AbstractVector>(new BitCompressedVectorAdapter<49>());
			break;
		case 50:
			m_vector = std::unique_ptr<AbstractVector>(new BitCompressedVectorAdapter<50>());
			break;
		case 51:
			m_vector = std::unique_ptr<AbstractVector>(new BitCompressedVectorAdapter<51>());
			break;
		case 52:
			m_vector = std::unique_ptr<AbstractVector>(new BitCompressedVectorAdapter<52>());
			break;
		case 53:
			m_vector = std::unique_ptr<AbstractVector>(new BitCompressedVectorAdapter<53>());
			break;
		case 54:
			m_vector = std::unique_ptr<AbstractVector>(new BitCompressedVectorAdapter<54>());
			break;
		case 55:
			m_vector = std::unique_ptr<AbstractVector>(new BitCompressedVectorAdapter<55>());
			break;
		case 56:
			m_vector = std::unique_ptr<AbstractVector>(new BitCompressedVectorAdapter<56>());
			break;
		case 57:
			m_vector = std::unique_ptr<AbstractVector>(new BitCompressedVectorAdapter<57>());
			break;
		case 58:
			m_vector = std::unique_ptr<AbstractVector>(new BitCompressedVectorAdapter<58>());
			break;
		case 59:
			m_vector = std::unique_ptr<AbstractVector>(new BitCompressedVectorAdapter<59>());
			break;
		case 60:
			m_vector = std::unique_ptr<AbstractVector>(new BitCompressedVectorAdapter<60>());
			break;
		case 61:
			m_vector = std::unique_ptr<AbstractVector>(new BitCompressedVectorAdapter<61>());
			break;
		case 62:
			m_vector = std::unique_ptr<AbstractVector>(new BitCompressedVectorAdapter<62>());
			break;
		case 63:
			m_vector = std::unique_ptr<AbstractVector>(new BitCompressedVectorAdapter<63>());
			break;
		case 64:
			m_vector = std::unique_ptr<AbstractVector>(new BitCompressedVectorAdapter<64>());
			break;
		default:
			printf("Number of bits not supported!");
		}
	}
};


#include "BitPackedVectorSIMD2.h"



#endif
// WITH_BCV

#endif
// BIT_PACKED_VECTOR_SIMD_H_
