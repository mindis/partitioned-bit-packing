
#include <stdio.h>
#include "tests/vector_tests.h"
#include "tests/column_tests.h"
#include "tests/data_generation_tests.h"


int main(int argc, char* argv[]) {
    printf("Program started.\n\n");

    
    run_vector_tests();
    run_column_tests();
    run_data_generation_tests();


    printf("\n\nProgram finished.\n");


#ifdef _WIN32
    return system("pause");
#else
    return 0;
#endif
}


