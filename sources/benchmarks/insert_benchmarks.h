#ifndef INSERT_BENCHMARKS_H_
#define INSERT_BENCHMARKS_H_


#include "vectors/PartitionedBitPackedVectors.h"
#include "benchmark/TimeBenchmarker.h"
#include "database/Dictionary.h"
#include "utils/utils.h"


ulong baseline_inserts(const ulong num_elements, const ulong distinct_values) {
    uint* data = new uint[num_elements];

    BasicBitPackedVector v(bitsNeeded(distinct_values));
    for (size_t n = 0; n < num_elements; ++n) {
        data[n] = rand() % distinct_values;
    }

    TimeBenchmarker timer(true);
    for (size_t n = 0; n < num_elements; ++n) {
        v.push_back(data[n]);
    }
    timer.stop();

    // Sanity check
    for (size_t n = 0; n < num_elements; ++n) {
    	if (v.get(n) != data[n]) printf("Error 1: There was an error in the benchmark.\n");
    }

    delete[] data;

    return timer.milliseconds();
}

ulong unpartitioned_inserts(const ulong num_elements, const ulong distinct_values) {
    uint* data = new uint[num_elements];
    uint* encoded = new uint[num_elements];
    uint* bits = new uint[num_elements];
    Dictionary<uint> dict = Dictionary<uint>(1);

    DynamicBitPackedVector v(1);
    for (size_t n = 0; n < num_elements; ++n) {
        data[n] = rand() % distinct_values;
        encoded[n] = dict.encode(data[n]);
        bits[n] = dict.getBits();
    }

    TimeBenchmarker timer(true);
    for (size_t n = 0; n < num_elements; ++n) {
    	v.setEncodingBits(bits[n]);
        v.push_back(encoded[n]);
    }
    timer.stop();

    // Sanity check
    for (size_t n = 0; n < num_elements; ++n) {
    	if (v.get(n) != encoded[n]) printf("Error 2: There was an error in the benchmark.\n");
    }

    delete[] data;
    delete[] bits;
    delete[] encoded;


    return timer.milliseconds();
}

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

    TimeBenchmarker timer(true);
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
	printf("Size\tDV\tBase\tD-BPV\tPBV\n");
	for (ulong num_elements = 100000; num_elements <= 10000000; num_elements *= 10) {
		for (ulong distinct_values = 1000; distinct_values <= 100000; distinct_values *= 10) {
			printf("%luk\t%luk\t%lu\t%lu\t%lu\n",
				num_elements / 1000,
				distinct_values / 1000,
				baseline_inserts(num_elements, distinct_values),
				unpartitioned_inserts(num_elements, distinct_values),
				partitioned_inserts(num_elements, distinct_values));
		}
	}


}


#endif