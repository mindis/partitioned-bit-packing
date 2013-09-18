#ifndef UTILS_H_
#define UTILS_H_


#include <math.h>

inline double log_2(double d) {
	return log(d)/log(2);
}

inline uint bitsNeeded(long val) {
	return ceil(log_2(val+1));
}


#endif