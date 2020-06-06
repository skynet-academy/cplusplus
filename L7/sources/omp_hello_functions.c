#include <omp.h>
#include <stdio.h>

void main() {
    omp_set_num_threads(4);
    
    #pragma omp parallel
    printf("Hellow word\n");
}