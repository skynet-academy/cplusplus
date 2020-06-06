#include <omp.h>
#include <stdio.h>

long fib(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;

    long i, j;

    // printf("Num threads: %d\n", omp_get_num_threads());

    #pragma omp parallel
    {
        #pragma omp sections
        {
            #pragma omp section
            {
                i = fib(n-1);
            }

            #pragma omp section
            {
                j = fib(n-2);
            }
        }
    }

    return i + j;
}

void main() {
    // omp_set_nested(1);

    long s = 0;
    s = fib(7);   
    
    printf("S: %ld\n", s);
}