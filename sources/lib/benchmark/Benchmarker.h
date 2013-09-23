#ifndef BENCHMARKER_H_
#define BENCHMARKER_H_

#include <stdlib.h>
#include <vector>
#include "os_defines.h"
#include "utils/utils.h"

template<typename _RESULT>
class Benchmarker {
public:
	Benchmarker(uint runs) : m_runs(runs), m_runNr(0) {

	}

	virtual _RESULT run() = 0;

	void runBenchmark() {
		for (uint n = 0; n < m_runs; ++n) {
			m_results.push_back(run());
			m_runNr++;
		}
	}

	std::vector<_RESULT>& results() { return m_results; }

	void clearResults() { m_results.clear(); }

	void setRuns(uint runs) { m_runs = runs; }

	void runs() { return m_runs; }

protected:
	uint m_runs, m_runNr;
	std::vector<_RESULT> m_results;
};


template<typename _NUMERIC>
class NumericBenchmarker : public Benchmarker<_NUMERIC> {
public:
	NumericBenchmarker(uint runs) : Benchmarker<_NUMERIC>(runs) {

	}

	double avg() {

		double avg = 0;
		for (uint n = 0; n < this->m_results.size(); ++n) {
			avg += this->m_results[n] / double(this->m_results.size());
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