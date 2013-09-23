#ifndef SIMD_ADAPTER_BENCHMARK_H_
#define SIMD_ADAPTER_BENCHMARK_H_


#include "vectors/BitPackedVectorSIMD.h"

#include "benchmark/Benchmarker.h"
#include "benchmark/Timer.h"

#include "utils/data_generation.h"



class BCVInsertBenchmark5 : public NumericBenchmarker<double> {
public:
	uint** m_data;
	uint m_size;
    BCVInsertBenchmark5(uint runs, uint size, uint** data) : NumericBenchmarker<double>(runs), m_data(data), m_size(size) {}
    double run() {
    	BitCompressedVector<uint, 5> v = BitCompressedVector<uint, 5>();
    	uint* data = m_data[m_runNr];
    	Timer timer(true);
        for (size_t n = 0; n < m_size; ++n) {
            v.push_back(data[n]);
        }
    	timer.stop();
    	return timer.microseconds() / 1000.0;
    }
};

class BCVAdapterInsertBenchmark5 : public NumericBenchmarker<double> {
public:
	uint** m_data;
	uint m_size;
    BCVAdapterInsertBenchmark5(uint runs, uint size, uint** data) : NumericBenchmarker<double>(runs), m_data(data), m_size(size) {}
    double run() {
    	BitCompressedVectorAdapter<5> v = BitCompressedVectorAdapter<5>();
    	uint* data = m_data[m_runNr];
    	Timer timer(true);
        for (size_t n = 0; n < m_size; ++n) {
            v.push_back(data[n]);
        }
    	timer.stop();
    	return timer.microseconds() / 1000.0;
    }
};


class SIMDVectorInsertBenchmark5 : public NumericBenchmarker<double> {
public:
	uint** m_data;
	uint m_size;
    SIMDVectorInsertBenchmark5(uint runs, uint size, uint** data) : NumericBenchmarker<double>(runs), m_data(data), m_size(size) {}
    double run() {
    	BitPackedVectorSIMD v(5);
    	uint* data = m_data[m_runNr];
    	Timer timer(true);
        for (size_t n = 0; n < m_size; ++n) {
            v.push_back(data[n]);
        }
    	timer.stop();
    	return timer.microseconds() / 1000.0;
    }
};



void run_simd_adapter_benchmarks() {
	const int runs = 10;
	int distinct_values = 20,
	    num_elements = 10000000;

    uint* data[runs];
    for (uint n = 0; n < runs; ++n) {
        data[n] = UniformGenerator::multiple(1, distinct_values, num_elements);
    }

    BCVInsertBenchmark5 bcv(runs, num_elements, data);
    BCVAdapterInsertBenchmark5 bcva(runs, num_elements, data);
    SIMDVectorInsertBenchmark5 simd(runs, num_elements, data);


    bcv.runBenchmark();
    bcva.runBenchmark();
    simd.runBenchmark();


    printf("%.2f\t%.2f\t%.2f\n", bcv.avg(), bcva.avg(), simd.avg());
}





#endif