#ifndef WIN_DEFINES_H_
#define WIN_DEFINES_H_

#ifdef _WIN32


#include <Windows.h>
#include <cmath>

typedef unsigned int uint;
typedef unsigned long ulong;

inline int round(double x) { return int(floor(x + 0.5)); }


#endif

#endif