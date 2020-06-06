#include <omp.h>
#include <stdio.h>

long fib(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;

    long i, j;

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

    return i + j;
}

void main() {
    long s = 0;
    #pragma omp parallel
    s = fib(7);   
    
    printf("S: %ld\n", s);
}