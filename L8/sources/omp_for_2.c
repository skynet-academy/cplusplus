#include <omp.h>
#include <stdio.h>

void main() {
    int A[10], B[10], C[10], i, n;

    // Initialize vars
    for(i=0; i<10; i++) {
        A[i] = i;
        B[i] = 2*i;
        C[i] = 0;
    }

    #pragma omp parallel shared(A, B, C) private(i, n)
    {
        n = omp_get_thread_num();

        #pragma omp for
        for(i=0; i<10; i++) {
            C[i] = A[i] + B[i];
            printf("Thread N%d compute item N%d\n", n, i);
        }
    }    
}