


members = "	BitCompressedVectorAdapter<%d> m_vector%d;"
gets = """		  case %d:
			return m_vector%d.get(index);"""
push_backs = """		  case %d:
			m_vector%d.push_back(val); break;"""
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

	uint get(const size_t index) {
		switch (m_bits) {"""
for n in instances:
	print gets % (n, n)
print """
		}
		return 0;
	}

	void push_back(uint val) {
		switch (m_bits) {"""
for n in instances:
	print push_backs % (n, n)
print """	
		}
	}

	size_t size() {
		return 0;
	}
};
"""