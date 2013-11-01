

#include <stdio.h>
// #include "benchmarks/simd_adapter_benchmarks.h"
#include "benchmarks/insert_benchmarks.h"
#include "benchmarks/scan_benchmarks.h"

int main(int argc, char* argv[]) {
	printf("Program started.\n\n");


	// run_insert_benchmarks();
	run_scan_benchmarks();
	// run_simd_adapter_benchmarks();


	printf("\n\nProgram finished.\n");


#ifdef _WIN32
	return system("pause");
#else
	return 0;
#endif
}