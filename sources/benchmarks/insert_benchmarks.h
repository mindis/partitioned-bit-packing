#ifndef INSERT_BENCHMARKS_H_
#define INSERT_BENCHMARKS_H_


#include "vectors/BasicBitPackedVector.h"
#include "benchmark/TimeBenchmarker.h"
#include "utils/utils.h"


void baseline_inserts(const ulong num_elements, const ulong distinct_values) {
    long* data = new long[num_elements];

    BasicBitPackedVector v(bitsNeeded(distinct_values));
    for (size_t n = 0; n < num_elements; ++n) {
        data[n] = rand() % distinct_values;
    }

    TimeBenchmarker timer(true);
    for (size_t n = 0; n < num_elements; ++n) {
        v.push_back(data[n]);
    }
    timer.stop();

    delete[] data;

    printf("%ld;%ld\n", num_elements, timer.microseconds());
}


void run_insert_benchmarks() {

	baseline_inserts(100000, 100);
	baseline_inserts(1000000, 100);
	baseline_inserts(10000000, 100);


}


#endif