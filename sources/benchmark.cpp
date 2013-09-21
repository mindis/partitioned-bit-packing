

#include <stdio.h>

int main(int argc, char* argv[]) {
    printf("Program started.\n\n");

    // run_insert_benchmarks();



    printf("\n\nProgram finished.\n");


#ifdef _WIN32
    return system("pause");
#else
    return 0;
#endif
}