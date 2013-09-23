#ifndef BIT_PACKED_VECTOR_SIMD_2_H_
#define BIT_PACKED_VECTOR_SIMD_2_H_


class BitPackedVectorSIMD2 : public AbstractBitPackedVector {
private:

	BitCompressedVectorAdapter<1> m_vector1;
	BitCompressedVectorAdapter<2> m_vector2;
	BitCompressedVectorAdapter<3> m_vector3;
	BitCompressedVectorAdapter<4> m_vector4;
	BitCompressedVectorAdapter<5> m_vector5;
	BitCompressedVectorAdapter<6> m_vector6;
	BitCompressedVectorAdapter<7> m_vector7;
	BitCompressedVectorAdapter<8> m_vector8;
	BitCompressedVectorAdapter<9> m_vector9;
	BitCompressedVectorAdapter<10> m_vector10;
	BitCompressedVectorAdapter<11> m_vector11;
	BitCompressedVectorAdapter<12> m_vector12;
	BitCompressedVectorAdapter<13> m_vector13;
	BitCompressedVectorAdapter<14> m_vector14;
	BitCompressedVectorAdapter<15> m_vector15;
	BitCompressedVectorAdapter<16> m_vector16;
	BitCompressedVectorAdapter<17> m_vector17;
	BitCompressedVectorAdapter<18> m_vector18;
	BitCompressedVectorAdapter<19> m_vector19;
	BitCompressedVectorAdapter<20> m_vector20;
	BitCompressedVectorAdapter<21> m_vector21;
	BitCompressedVectorAdapter<22> m_vector22;
	BitCompressedVectorAdapter<23> m_vector23;
	BitCompressedVectorAdapter<24> m_vector24;
	BitCompressedVectorAdapter<25> m_vector25;
	BitCompressedVectorAdapter<26> m_vector26;
	BitCompressedVectorAdapter<27> m_vector27;
	BitCompressedVectorAdapter<28> m_vector28;
	BitCompressedVectorAdapter<29> m_vector29;
	BitCompressedVectorAdapter<30> m_vector30;
	BitCompressedVectorAdapter<31> m_vector31;
	BitCompressedVectorAdapter<32> m_vector32;
	BitCompressedVectorAdapter<33> m_vector33;
	BitCompressedVectorAdapter<34> m_vector34;
	BitCompressedVectorAdapter<35> m_vector35;
	BitCompressedVectorAdapter<36> m_vector36;
	BitCompressedVectorAdapter<37> m_vector37;
	BitCompressedVectorAdapter<38> m_vector38;
	BitCompressedVectorAdapter<39> m_vector39;
	BitCompressedVectorAdapter<40> m_vector40;
	BitCompressedVectorAdapter<41> m_vector41;
	BitCompressedVectorAdapter<42> m_vector42;
	BitCompressedVectorAdapter<43> m_vector43;
	BitCompressedVectorAdapter<44> m_vector44;
	BitCompressedVectorAdapter<45> m_vector45;
	BitCompressedVectorAdapter<46> m_vector46;
	BitCompressedVectorAdapter<47> m_vector47;
	BitCompressedVectorAdapter<48> m_vector48;
	BitCompressedVectorAdapter<49> m_vector49;
	BitCompressedVectorAdapter<50> m_vector50;
	BitCompressedVectorAdapter<51> m_vector51;
	BitCompressedVectorAdapter<52> m_vector52;
	BitCompressedVectorAdapter<53> m_vector53;
	BitCompressedVectorAdapter<54> m_vector54;
	BitCompressedVectorAdapter<55> m_vector55;
	BitCompressedVectorAdapter<56> m_vector56;
	BitCompressedVectorAdapter<57> m_vector57;
	BitCompressedVectorAdapter<58> m_vector58;
	BitCompressedVectorAdapter<59> m_vector59;
	BitCompressedVectorAdapter<60> m_vector60;
	BitCompressedVectorAdapter<61> m_vector61;
	BitCompressedVectorAdapter<62> m_vector62;
	BitCompressedVectorAdapter<63> m_vector63;
	BitCompressedVectorAdapter<64> m_vector64;

	uint m_bits;

public:
	BitPackedVectorSIMD2(uint bits) : m_bits(bits) {}

	inline void setEncodingBits(uint bits) {}
	inline uint bits() { return m_bits; }

	uint get(const size_t index) {
		if (m_bits == 1) { return m_vector1.get(index); }
		if (m_bits == 2) { return m_vector2.get(index); }
		if (m_bits == 3) { return m_vector3.get(index); }
		if (m_bits == 4) { return m_vector4.get(index); }
		if (m_bits == 5) { return m_vector5.get(index); }
		if (m_bits == 6) { return m_vector6.get(index); }
		if (m_bits == 7) { return m_vector7.get(index); }
		if (m_bits == 8) { return m_vector8.get(index); }
		if (m_bits == 9) { return m_vector9.get(index); }
		if (m_bits == 10) { return m_vector10.get(index); }
		if (m_bits == 11) { return m_vector11.get(index); }
		if (m_bits == 12) { return m_vector12.get(index); }
		if (m_bits == 13) { return m_vector13.get(index); }
		if (m_bits == 14) { return m_vector14.get(index); }
		if (m_bits == 15) { return m_vector15.get(index); }
		if (m_bits == 16) { return m_vector16.get(index); }
		if (m_bits == 17) { return m_vector17.get(index); }
		if (m_bits == 18) { return m_vector18.get(index); }
		if (m_bits == 19) { return m_vector19.get(index); }
		if (m_bits == 20) { return m_vector20.get(index); }
		if (m_bits == 21) { return m_vector21.get(index); }
		if (m_bits == 22) { return m_vector22.get(index); }
		if (m_bits == 23) { return m_vector23.get(index); }
		if (m_bits == 24) { return m_vector24.get(index); }
		if (m_bits == 25) { return m_vector25.get(index); }
		if (m_bits == 26) { return m_vector26.get(index); }
		if (m_bits == 27) { return m_vector27.get(index); }
		if (m_bits == 28) { return m_vector28.get(index); }
		if (m_bits == 29) { return m_vector29.get(index); }
		if (m_bits == 30) { return m_vector30.get(index); }
		if (m_bits == 31) { return m_vector31.get(index); }
		if (m_bits == 32) { return m_vector32.get(index); }
		if (m_bits == 33) { return m_vector33.get(index); }
		if (m_bits == 34) { return m_vector34.get(index); }
		if (m_bits == 35) { return m_vector35.get(index); }
		if (m_bits == 36) { return m_vector36.get(index); }
		if (m_bits == 37) { return m_vector37.get(index); }
		if (m_bits == 38) { return m_vector38.get(index); }
		if (m_bits == 39) { return m_vector39.get(index); }
		if (m_bits == 40) { return m_vector40.get(index); }
		if (m_bits == 41) { return m_vector41.get(index); }
		if (m_bits == 42) { return m_vector42.get(index); }
		if (m_bits == 43) { return m_vector43.get(index); }
		if (m_bits == 44) { return m_vector44.get(index); }
		if (m_bits == 45) { return m_vector45.get(index); }
		if (m_bits == 46) { return m_vector46.get(index); }
		if (m_bits == 47) { return m_vector47.get(index); }
		if (m_bits == 48) { return m_vector48.get(index); }
		if (m_bits == 49) { return m_vector49.get(index); }
		if (m_bits == 50) { return m_vector50.get(index); }
		if (m_bits == 51) { return m_vector51.get(index); }
		if (m_bits == 52) { return m_vector52.get(index); }
		if (m_bits == 53) { return m_vector53.get(index); }
		if (m_bits == 54) { return m_vector54.get(index); }
		if (m_bits == 55) { return m_vector55.get(index); }
		if (m_bits == 56) { return m_vector56.get(index); }
		if (m_bits == 57) { return m_vector57.get(index); }
		if (m_bits == 58) { return m_vector58.get(index); }
		if (m_bits == 59) { return m_vector59.get(index); }
		if (m_bits == 60) { return m_vector60.get(index); }
		if (m_bits == 61) { return m_vector61.get(index); }
		if (m_bits == 62) { return m_vector62.get(index); }
		if (m_bits == 63) { return m_vector63.get(index); }
		if (m_bits == 64) { return m_vector64.get(index); }

		return 0;
	}

	void push_back(uint val) {
		if (m_bits == 1) { m_vector1.push_back(val); return; }
		if (m_bits == 2) { m_vector2.push_back(val); return; }
		if (m_bits == 3) { m_vector3.push_back(val); return; }
		if (m_bits == 4) { m_vector4.push_back(val); return; }
		if (m_bits == 5) { m_vector5.push_back(val); return; }
		if (m_bits == 6) { m_vector6.push_back(val); return; }
		if (m_bits == 7) { m_vector7.push_back(val); return; }
		if (m_bits == 8) { m_vector8.push_back(val); return; }
		if (m_bits == 9) { m_vector9.push_back(val); return; }
		if (m_bits == 10) { m_vector10.push_back(val); return; }
		if (m_bits == 11) { m_vector11.push_back(val); return; }
		if (m_bits == 12) { m_vector12.push_back(val); return; }
		if (m_bits == 13) { m_vector13.push_back(val); return; }
		if (m_bits == 14) { m_vector14.push_back(val); return; }
		if (m_bits == 15) { m_vector15.push_back(val); return; }
		if (m_bits == 16) { m_vector16.push_back(val); return; }
		if (m_bits == 17) { m_vector17.push_back(val); return; }
		if (m_bits == 18) { m_vector18.push_back(val); return; }
		if (m_bits == 19) { m_vector19.push_back(val); return; }
		if (m_bits == 20) { m_vector20.push_back(val); return; }
		if (m_bits == 21) { m_vector21.push_back(val); return; }
		if (m_bits == 22) { m_vector22.push_back(val); return; }
		if (m_bits == 23) { m_vector23.push_back(val); return; }
		if (m_bits == 24) { m_vector24.push_back(val); return; }
		if (m_bits == 25) { m_vector25.push_back(val); return; }
		if (m_bits == 26) { m_vector26.push_back(val); return; }
		if (m_bits == 27) { m_vector27.push_back(val); return; }
		if (m_bits == 28) { m_vector28.push_back(val); return; }
		if (m_bits == 29) { m_vector29.push_back(val); return; }
		if (m_bits == 30) { m_vector30.push_back(val); return; }
		if (m_bits == 31) { m_vector31.push_back(val); return; }
		if (m_bits == 32) { m_vector32.push_back(val); return; }
		if (m_bits == 33) { m_vector33.push_back(val); return; }
		if (m_bits == 34) { m_vector34.push_back(val); return; }
		if (m_bits == 35) { m_vector35.push_back(val); return; }
		if (m_bits == 36) { m_vector36.push_back(val); return; }
		if (m_bits == 37) { m_vector37.push_back(val); return; }
		if (m_bits == 38) { m_vector38.push_back(val); return; }
		if (m_bits == 39) { m_vector39.push_back(val); return; }
		if (m_bits == 40) { m_vector40.push_back(val); return; }
		if (m_bits == 41) { m_vector41.push_back(val); return; }
		if (m_bits == 42) { m_vector42.push_back(val); return; }
		if (m_bits == 43) { m_vector43.push_back(val); return; }
		if (m_bits == 44) { m_vector44.push_back(val); return; }
		if (m_bits == 45) { m_vector45.push_back(val); return; }
		if (m_bits == 46) { m_vector46.push_back(val); return; }
		if (m_bits == 47) { m_vector47.push_back(val); return; }
		if (m_bits == 48) { m_vector48.push_back(val); return; }
		if (m_bits == 49) { m_vector49.push_back(val); return; }
		if (m_bits == 50) { m_vector50.push_back(val); return; }
		if (m_bits == 51) { m_vector51.push_back(val); return; }
		if (m_bits == 52) { m_vector52.push_back(val); return; }
		if (m_bits == 53) { m_vector53.push_back(val); return; }
		if (m_bits == 54) { m_vector54.push_back(val); return; }
		if (m_bits == 55) { m_vector55.push_back(val); return; }
		if (m_bits == 56) { m_vector56.push_back(val); return; }
		if (m_bits == 57) { m_vector57.push_back(val); return; }
		if (m_bits == 58) { m_vector58.push_back(val); return; }
		if (m_bits == 59) { m_vector59.push_back(val); return; }
		if (m_bits == 60) { m_vector60.push_back(val); return; }
		if (m_bits == 61) { m_vector61.push_back(val); return; }
		if (m_bits == 62) { m_vector62.push_back(val); return; }
		if (m_bits == 63) { m_vector63.push_back(val); return; }
		if (m_bits == 64) { m_vector64.push_back(val); return; }
	
	}

	size_t size() {
		return 0;
	}
};

#endif