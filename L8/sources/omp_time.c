#include <omp.h>
#include <stdio.h>

void main() {
    double start_time, end_time, tick;

    start_time = omp_get_wtime();
    end_time = omp_get_wtime();

    tick = omp_get_wtick();

    printf("Time: %0.10lf\n", end_time - start_time);
    printf("Timer accuracy: %0.10lf\n", tick);
}