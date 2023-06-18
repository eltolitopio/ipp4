#ifdef _OPENMP
#include <omp.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "mymatrix.h"

int main(int argc, char *argv[]) {
    matrix *a;
    matrix *b;
    const int x = (int) strtoul(argv[1], NULL, 10);
    const int y = (int) strtoul(argv[2], NULL, 10);
    UNUSED(argc);

    srand((unsigned int) time(0UL));

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            initmatrix(&a, x, y);
            fillmatrix(a);
        }

        #pragma omp section
        {
            initmatrix(&b, x, y);
            fillmatrix(b);
        }
    }

    printf("a:\n");
    printmatrix(a);

    printf("b:\n");
    printmatrix(b);

    submatrix(a, b);

    printf("res:\n");
    printmatrix(a);

    averagematrix(a);
    printaboveaveragematrix(a);

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            freematrix(a);
        }

        #pragma omp section
        {
            freematrix(b);
        }
    }

    return 0;
}
