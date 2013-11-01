#ifndef SCAN_OP_H
#define SCAN_OP_H


template<typename _VECTOR>
class EqScanOp {
private:
	_VECTOR* _vector;
	size_t _matches;

public:
	EqScanOp(_VECTOR* vector) {
		_vector = vector;
	}

	void scan(uint field_code) {
		size_t num_elements = _vector->size();
		_matches = 0;
        for (size_t n = 0; n < num_elements; ++n) {
            if (_vector->get(n) == 10) _matches++;
        }
	}

	inline size_t matches() { return _matches; }
};



template<typename _PARTVECTOR, typename _VECTOR>
class EqPartitionedScanOp {
private:
	_PARTVECTOR* _vector;
	size_t _matches;

public:
	EqPartitionedScanOp(_PARTVECTOR* vector) {
		_vector = vector;
	}

	void scan(uint field_code) {
		size_t num_elements = _vector->size();
		_matches = 0;

		std::vector<_VECTOR*> vectors = _vector->vectors();
		for (uint vid = _vector->baseEncoding(); vid < vectors.size() && vectors[vid]->size() != 0; ++vid) {
			for (uint n = 0; n < vectors[vid]->size(); ++n) {
				if (vectors[vid]->get(n) == field_code) _matches++;
			}
		}
	}

	inline size_t matches() { return _matches; }
};



#endif