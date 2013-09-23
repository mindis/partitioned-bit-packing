


members = "	BitCompressedVectorAdapter<%d> m_vector%d;"
gets = "		if (m_bits == %d) { return m_vector%d.get(index); }"
push_backs = "		if (m_bits == %d) { m_vector%d.push_back(val); return; }"
instances = range(1, 65)


print """
class BitPackedVectorSIMD2 : public AbstractBitPackedVector {
private:
"""
for n in instances:
	print members % (n, n)

print """
	uint m_bits;

public:
	BitPackedVectorSIMD2(uint bits) : m_bits(bits) {}

	inline void setEncodingBits(uint bits) {}
	inline uint bits() { return m_bits; }

	uint get(const size_t index) {"""
for n in instances:
	print gets % (n, n)
print """
		return 0;
	}

	void push_back(uint val) {"""
for n in instances:
	print push_backs % (n, n)
print """	
	}

	size_t size() {
		return 0;
	}
};
"""