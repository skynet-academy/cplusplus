#include <omp.h>
#include <stdio.h>

// NOTE: There are more efficient algorithms for computing Fibbonacci numbers!
// This classic recursion alg is for illustrative purposes!

long fib(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;

    return fib(n-1) + fib(n-2);
}

void main() {
    long s = fib(7);
    
    printf("S: %ld\n", s);
}