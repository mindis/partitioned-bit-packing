#ifndef INSERT_BENCHMARKS_H_
#define INSERT_BENCHMARKS_H_


#include "vectors/BitPackedVectorSIMD.h"
#include "vectors/PartitionedVectorTemplate.h"
#include "vectors/PartitionedBitPackedVectors.h"
#include "benchmark/Timer.h"
#include "database/Dictionary.h"
#include "utils/utils.h"
#include "benchmark/Benchmarker.h"
#include "utils/data_generation.h"


class InsertBenchmarker : public NumericBenchmarker<double> {
public:
    size_t m_numElements, m_distinctValues;
    uint** m_data;
    InsertBenchmarker(uint runs, size_t numElements, size_t distinctValues, uint** data) : NumericBenchmarker<double>(runs) {
        m_data = data;
        m_numElements = numElements;
        m_distinctValues = distinctValues;
    }
};



class BaselineInsertBenchmarker : public InsertBenchmarker {
public:
    BaselineInsertBenchmarker(uint r, size_t n, size_t dv, uint** data) : InsertBenchmarker(r, n, dv, data) {}
    
    double run() {
        BasicBitPackedVector v(bitsNeeded(m_distinctValues));

        Timer timer(true);
        for (size_t n = 0; n < m_numElements; ++n) {
            v.push_back(m_data[m_runNr][n]);
        }
        timer.stop();

        // Sanity check
        for (size_t n = 0; n < m_numElements; ++n) {
            if (v.get(n) != m_data[m_runNr][n]) printf("Error 1: There was an error in the benchmark.\n");
        }

        return timer.microseconds() / 1000.0;
    }
};


class BaseSIMDInsertBenchmarker : public InsertBenchmarker {
public:
    BaseSIMDInsertBenchmarker(uint r, size_t n, size_t dv, uint** data) : InsertBenchmarker(r, n, dv, data) {}
    
    double run() {
        BitPackedVectorSIMD v(bitsNeeded(m_distinctValues));

        Timer timer(true);
        for (size_t n = 0; n < m_numElements; ++n) {
            v.push_back(m_data[m_runNr][n]);
        }
        timer.stop();

        // Sanity check
        for (size_t n = 0; n < m_numElements; ++n) {
            if (v.get(n) != m_data[m_runNr][n]) printf("Error 2: There was an error in the benchmark.\n");
        }

        return timer.microseconds() / 1000.0;
    }
};



ulong partitioned_inserts(const ulong num_elements, const ulong distinct_values) {
    uint* data = new uint[num_elements];
    uint* encoded = new uint[num_elements];
    uint* bits = new uint[num_elements];
    Dictionary<uint> dict = Dictionary<uint>(1);

    PartitionedBitPackedVector_Get_3 v(1);
    for (size_t n = 0; n < num_elements; ++n) {
        data[n] = rand() % distinct_values;
        encoded[n] = dict.encode(data[n]);
        bits[n] = dict.getBits();
    }

    Timer timer(true);
    for (size_t n = 0; n < num_elements; ++n) {
        v.setEncodingBits(bits[n]);
        v.push_back(encoded[n]);
    }
    timer.stop();

    // Sanity check
    for (size_t n = 0; n < num_elements; ++n) {
        if (v.get(n) != encoded[n]) printf("Error 3: There was an error in the benchmark.\n");
    }

    delete[] data;
    delete[] bits;
    delete[] encoded;

    return timer.milliseconds();
}

ulong partitioned_simd_inserts(const ulong num_elements, const ulong distinct_values) {
    uint* data = new uint[num_elements];
    uint* encoded = new uint[num_elements];
    uint* bits = new uint[num_elements];
    Dictionary<uint> dict = Dictionary<uint>(1);

    PartitionedVectorTemplate<BitPackedVectorSIMD> v(1);
    for (size_t n = 0; n < num_elements; ++n) {
        data[n] = rand() % distinct_values;
        encoded[n] = dict.encode(data[n]);
        bits[n] = dict.getBits();
    }

    Timer timer(true);
    for (size_t n = 0; n < num_elements; ++n) {
        v.setEncodingBits(bits[n]);
        v.push_back(encoded[n]);
    }
    timer.stop();

    // Sanity check
    for (size_t n = 0; n < num_elements; ++n) {
        if (v.get(n) != encoded[n]) printf("Error 3: There was an error in the benchmark.\n");
    }

    delete[] data;
    delete[] bits;
    delete[] encoded;

    return timer.milliseconds();
}


void run_insert_benchmarks() {
	printf("Insert Benchmark\n");

    const uint runs = 10;

    printf("Size\tDV\tBase\tSIMD\tP-BPV\tP-SIMD\n");
    for (ulong num_elements = 100000; num_elements <= 1000000; num_elements *= 10) {
        for (ulong distinct_values = 1000; distinct_values <= 100000; distinct_values *= 10) {

            uint* data[runs];
            for (uint n = 0; n < runs; ++n) {
                data[n] = UniformGenerator::multiple(1, distinct_values, num_elements);
            }

            BaseSIMDInsertBenchmarker b2(10, num_elements, distinct_values, data);
            b2.runBenchmark();
            
            BaselineInsertBenchmarker b1(10, num_elements, distinct_values, data);
            b1.runBenchmark();


   
            printf("%luk\t%luk\t%.2f\t%.2f\n",
                num_elements / 1000,
                distinct_values / 1000,
                b1.avg(), b2.avg());
        }
    }
    /*
	printf("Size\tDV\tBase\tSIMD\tP-BPV\tP-SIMD\n");
	for (ulong num_elements = 100000; num_elements <= 10000000; num_elements *= 10) {
		for (ulong distinct_values = 1000; distinct_values <= 100000; distinct_values *= 10) {
			printf("%luk\t%luk\t%lu\t%lu\t%lu\t%lu\n",
				num_elements / 1000,
				distinct_values / 1000,
				baseline_inserts(num_elements, distinct_values),
				baseline_simd_inserts(num_elements, distinct_values),
				partitioned_inserts(num_elements, distinct_values),
                partitioned_simd_inserts(num_elements, distinct_values));
		}
	}
    */
}


#endif