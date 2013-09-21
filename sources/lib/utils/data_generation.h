#ifndef DATA_GENERATION_H_
#define DATA_GENERATION_H_

#include <stdlib.h>
#include "os_defines.h"

namespace utils {
	void fast_srand(int seed);
	unsigned int fastrand();
}





class UniformGenerator {
public:
	static uint single(uint from, uint to) {
		return from + utils::fastrand() % (to-from + 1);
	}
	static uint* multiple(uint from, uint to, size_t size) {
		uint* array = new uint[size];
		for (size_t n = 0; n < size; ++n) array[n] = UniformGenerator::single(from, to);
		return array;
	}
};




#endif