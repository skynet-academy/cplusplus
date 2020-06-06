#include <omp.h>
#include <stdio.h>

// NOTE: There are more efficient algorithms for computing Fibbonacci numbers!
// This classic recursion alg is for illustrative purposes!

long fib(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;

    long i, j;

    #pragma omp task shared(i) firstprivate(n)
    i = fib(n-1);

    #pragma omp task shared(j) firstprivate(n)
    j = fib(n-2);
    
    #pragma omp taskwait
    return i + j;
}

void main() {    
    long s = 0;

    #pragma omp parallel
    {
        #pragma omp single
        s = fib(35);   
    }    
    
    printf("S: %ld\n", s);
}