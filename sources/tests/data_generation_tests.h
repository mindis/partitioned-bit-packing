#ifndef DATA_GENERATION_TESTS_H_
#define DATA_GENERATION_TESTS_H_

#include "lib/utils/data_generation.h"

namespace testutils {
	long min(long* array, size_t size) {
		long minimum = array[0];
		for (size_t n = 1; n < size; ++n) {
			if (array[n] < minimum)
				minimum = array[n];
		}
		return minimum;
	}

	long max(long* array, size_t size) {
		long maximum = array[0];
		for (size_t n = 1; n < size; ++n) {
			if (array[n] > maximum)
				maximum = array[n];
		}
		return maximum;
	}
}

bool uniform_range_test(long from, long to, size_t size) {
	long* data = UniformGenerator::multiple(from, to, size);

	long minv = testutils::min(data, size),
	     maxv = testutils::max(data, size);

	if (minv == from && maxv == to) {
		printf("Uniform Range Test passed!\n");
	} else {
		printf("Uniform Range Test failed: Expected %ld-%ld. Got %ld-%ld.\n", from, to, minv, maxv);
	}

	return true;
}



bool run_data_generation_tests() {
	bool ok = true;


	ok &= uniform_range_test(0, 100, 10000);
	ok &= uniform_range_test(100, 500, 10000);
	ok &= uniform_range_test(-100, 100, 10000);


	return ok;
}


#endif