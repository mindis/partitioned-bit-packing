
#include <stdio.h>
#include "tests/vector_tests.h"


int main(int argc, char* argv[]) {
	printf("Program started.\n\n");

    
    run_vector_tests();



	printf("\n\nProgram finished.\n");


#ifdef _WIN32
    return system("pause");
#else
	return 0;
#endif
}


