
#include <stdio.h>
#include "tests/vector_tests.h"
#include "tests/column_tests.h"
#include "benchmarks/insert_benchmarks.h"


int main(int argc, char* argv[]) {
    printf("Program started.\n\n");

    
    run_vector_tests();
    run_column_tests();

    run_insert_benchmarks();



    printf("\n\nProgram finished.\n");


#ifdef _WIN32
    return system("pause");
#else
    return 0;
#endif
}


