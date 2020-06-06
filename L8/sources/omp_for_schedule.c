#include <omp.h>
#include <stdio.h>
#include <unistd.h>

void main() {
    int i;

    #pragma omp parallel num_threads(4) private(i)
    {
        #pragma omp for schedule (static) // (static, 1), (dynamic)
        for(int i=0; i<12; i++) {
            printf("Thread N%d compute iteration N%d\n", omp_get_thread_num(), i);
            sleep(1);
        }    
    }
}