#include <omp.h>
#include <stdio.h>

void main() {
    #pragma omp parallel for
    for(int i=0; i<100; i++) {
        printf("%d\n", i);
    }    
}