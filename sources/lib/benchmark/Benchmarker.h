#ifndef BENCHMARKER_H_
#define BENCHMARKER_H_

#include <stdlib.h>
#include <vector>
#include "os_defines.h"
#include "utils/utils.h"

template<typename _RESULT>
class Benchmarker {
public:
	Benchmarker(uint runs) : _runs(runs), _run_nr(0) {

	}

	virtual _RESULT run() = 0;

	void runBenchmark() {
		for (uint n = 0; n < _runs; ++n) {
			_results.push_back(run());
			_run_nr++;
		}
	}

	std::vector<_RESULT>& results() { return _results; }

	void clearResults() { _results.clear(); }

	void setRuns(uint runs) { _runs = runs; }

	void runs() { return _runs; }

protected:
	uint _runs, _run_nr;
	std::vector<_RESULT> _results;
};


template<typename _NUMERIC>
class NumericBenchmarker : public Benchmarker<_NUMERIC> {
public:
	NumericBenchmarker(uint runs) : Benchmarker<_NUMERIC>(runs) {

	}

	double avg() {

		double avg = 0;
		for (uint n = 0; n < this->_results.size(); ++n) {
			avg += this->_results[n] / double(this->_results.size());
		}
		return avg;
	}

	double max() {
		return 0.0;
	}

	double min() {
		return 0.0;
	}
};


#endif