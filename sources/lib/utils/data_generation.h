#ifndef DATA_GENERATION_H_
#define DATA_GENERATION_H_

#include <stdlib.h>

namespace utils {
	void fast_srand(int seed);
	unsigned int fastrand();
}





class UniformGenerator {
public:
	static long single(long from, long to) {
		return from + utils::fastrand() % (to-from + 1);
	}
	static long* multiple(long from, long to, size_t size) {
		long* array = new long[size];
		for (size_t n = 0; n < size; ++n) array[n] = UniformGenerator::single(from, to);
		return array;
	}
};




#endif