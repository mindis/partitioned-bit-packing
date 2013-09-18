#ifndef DICTIONARY_H_
#define DICTIONARY_H_

#include <vector>
#include <map>
#include <math.h>
#include <stdlib.h>

// typedef unsigned int field_code_t;

template <typename _T>
class Dictionary {
private:
    std::map<_T, uint> m_encodeMap;
    std::vector<_T> m_decodeMap;

    uint m_distinctValues;
    uint m_bits, m_bitValues;

public:
    Dictionary() : m_distinctValues(0), m_bits(1), m_bitValues(2) {}
    Dictionary(uint startBits) : m_distinctValues(0) {
        if (startBits < 1) printf("Start bits of a dictionary is not supposed to be less than 1!");
        m_bits = startBits;
        m_bitValues = uint(pow(2, m_bits));
    }

    uint encode(const _T& val) {
        if (m_encodeMap.find(val) == m_encodeMap.end()) {
            uint code = m_distinctValues;

            if (m_distinctValues+1 > m_bitValues) {
                m_bits++;
                m_bitValues = uint(pow(2, m_bits));
            }

            m_distinctValues++;

            m_encodeMap.insert(std::make_pair(val, code));
            m_decodeMap.push_back(val);
            return code;
        }
        return m_encodeMap[val];
    }

    _T& decode(uint val) {
        return m_decodeMap[val];
    }

    uint getBits() {
        return m_bits;
    }

    uint getDistinctValues() {
        return m_distinctValues;
    }
};


#endif