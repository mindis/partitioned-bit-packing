#ifndef COLUMN_H_
#define COLUMN_H_

#include "database/AbstractColumn.h"
#include "database/Dictionary.h"


template <typename _T_VECTOR, typename _T_VALUE>
class Column : public AbstractColumn<_T_VALUE> {
private:
	Dictionary<_T_VALUE>* m_dict;
	_T_VECTOR* m_vector;
	size_t m_size;

public:
	Column(uint encodingBits) {
		m_dict = new Dictionary<_T_VALUE>(encodingBits);
		m_vector = new _T_VECTOR(encodingBits);
		m_size = 0;
	}

	~Column() {
		delete m_vector;
		delete m_dict;
	}

	void push_back(const _T_VALUE& value) {
		uint fieldcode = m_dict->encode(value);
		m_vector->setEncodingBits(m_dict->getBits());
		m_vector->push_back(fieldcode);
		m_size++;
	}

	_T_VALUE& get(const uint index) {
		uint fieldcode = m_vector->get(index);
		return m_dict->decode(fieldcode);
	}

	void printBits() {
		m_vector->printBits();
	}

	size_t size() {
		return m_size;
	}

	Dictionary<_T_VALUE>* dict() {
		return m_dict;
	}

	_T_VECTOR* vector() {
		return m_vector;
	}

	uint getFieldCode(_T_VALUE value) {
		return m_dict->encode(value);
	}
};




#endif