#ifndef SIMD_ADAPTER_BENCHMARK_H_
#define SIMD_ADAPTER_BENCHMARK_H_


#include "vectors/BitPackedVectorSIMD.h"
#include "vectors/BitPackedVectorSIMD2.h"

#include "benchmark/Benchmarker.h"
#include "benchmark/Timer.h"

#include "utils/data_generation.h"


#define BITS 10


class BCVInsertBenchmark_ : public NumericBenchmarker<double> {
public:
	uint** m_data;
	uint m_size;
    BCVInsertBenchmark_(uint runs, uint size, uint** data) : NumericBenchmarker<double>(runs), m_data(data), m_size(size) {}
    double run() {
    	BitCompressedVector<uint, BITS> v = BitCompressedVector<uint, BITS>();
    	uint* data = m_data[_run_nr];
    	Timer timer(true);
        for (size_t n = 0; n < m_size; ++n) {
            v.push_back(data[n]);
        }
    	timer.stop();
    	return timer.microseconds() / 1000.0;
    }
};

class BCVAdapterInsertBenchmark_ : public NumericBenchmarker<double> {
public:
	uint** m_data;
	uint m_size;
    BCVAdapterInsertBenchmark_(uint runs, uint size, uint** data) : NumericBenchmarker<double>(runs), m_data(data), m_size(size) {}
    double run() {
    	BitCompressedVectorAdapter<BITS> v = BitCompressedVectorAdapter<BITS>();
    	uint* data = m_data[_run_nr];
    	Timer timer(true);
        for (size_t n = 0; n < m_size; ++n) {
            v.push_back(data[n]);
        }
    	timer.stop();
    	return timer.microseconds() / 1000.0;
    }
};


class SIMDVectorInsertBenchmark_ : public NumericBenchmarker<double> {
public:
	uint** m_data;
	uint m_size;
    SIMDVectorInsertBenchmark_(uint runs, uint size, uint** data) : NumericBenchmarker<double>(runs), m_data(data), m_size(size) {}
    double run() {
    	BitPackedVectorSIMD v(BITS);
    	uint* data = m_data[_run_nr];
    	Timer timer(true);
        for (size_t n = 0; n < m_size; ++n) {
            v.push_back(data[n]);
        }
    	timer.stop();
    	return timer.microseconds() / 1000.0;
    }
};
class SIMDVector2InsertBenchmark_ : public NumericBenchmarker<double> {

public:
	uint** m_data;
	uint m_size;
    SIMDVector2InsertBenchmark_(uint runs, uint size, uint** data) : NumericBenchmarker<double>(runs), m_data(data), m_size(size) {}
    double run() {
    	BitPackedVectorSIMD2 v(BITS);
    	uint* data = m_data[_run_nr];
    	Timer timer(true);
        for (size_t n = 0; n < m_size; ++n) {
            v.push_back(data[n]);
        }
    	timer.stop();
    	return timer.microseconds() / 1000.0;
    }
};



void run_simd_adapter_benchmarks() {
	const int runs = 5;
	int distinct_values = 1000;

    printf("#\tBCV\tBCV-A\tSIMD\n");

    for (uint num_elements = 100000; num_elements <= 100000000; num_elements *= 10) {
        uint* data[runs];
        for (uint n = 0; n < runs; ++n) {
            data[n] = UniformGenerator::multiple(1, distinct_values, num_elements);
        }

        BCVInsertBenchmark_ bcv(runs, num_elements, data);
        BCVAdapterInsertBenchmark_ bcva(runs, num_elements, data);
        SIMDVectorInsertBenchmark_ simd(runs, num_elements, data);

        bcva.runBenchmark();
        bcv.runBenchmark();
        simd.runBenchmark();

        printf("%uk\t%.2f\t%.2f\t%.2f\n", num_elements/1000, bcv.avg(), bcva.avg(), simd.avg());

        for (uint n = 0; n < runs; ++n) {
            delete[] data[n];
        }
    }
}



#endif