#include <omp.h>
#include <stdio.h>

// export OMP_NUM_THREADS=4 && ./a.out

void main() {
    #pragma omp parallel
    printf("Hellow word\n");
}