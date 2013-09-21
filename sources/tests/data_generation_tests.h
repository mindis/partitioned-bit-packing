#ifndef DATA_GENERATION_TESTS_H_
#define DATA_GENERATION_TESTS_H_

#include "lib/utils/data_generation.h"

namespace testutils {
	uint min(uint* array, size_t size) {
		uint minimum = array[0];
		for (size_t n = 1; n < size; ++n) {
			if (array[n] < minimum)
				minimum = array[n];
		}
		return minimum;
	}

	uint max(uint* array, size_t size) {
		uint maximum = array[0];
		for (size_t n = 1; n < size; ++n) {
			if (array[n] > maximum)
				maximum = array[n];
		}
		return maximum;
	}
}

bool uniform_range_test(uint from, uint to, size_t size) {
	uint* data = UniformGenerator::multiple(from, to, size);

	uint minv = testutils::min(data, size),
	     maxv = testutils::max(data, size);

	if (minv == from && maxv == to) {
		printf("Uniform Range Test passed!\n");
	} else {
		printf("Uniform Range Test failed: Expected %u-%u. Got %u-%u.\n", from, to, minv, maxv);
	}

	return true;
}



bool run_data_generation_tests() {
	bool ok = true;


	ok &= uniform_range_test(0, 100, 10000);
	ok &= uniform_range_test(100, 500, 10000);
	ok &= uniform_range_test(1000, 2000, 100000);


	return ok;
}


#endif