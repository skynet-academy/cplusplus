#include <omp.h>
#include <stdio.h>

void main() {
    #pragma omp parallel
    printf("ID: %d\n", omp_get_thread_num());
}