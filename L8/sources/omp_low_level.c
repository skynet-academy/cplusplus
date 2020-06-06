#include <omp.h>
#include <stdio.h>

void main() {
    int count, num;
    #pragma omp parallel 
    {
        count = omp_get_num_threads();
        num = omp_get_thread_num();

        if (num == 0) {
            printf("Total thread count: %d\n", count);
        }
        else {
            printf("Thread id: %d\n", num);
        }
    }
}