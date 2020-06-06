#include <omp.h>
#include <stdio.h>

void main() {
    #pragma omp parallel
    printf("Hellow word\n");
}