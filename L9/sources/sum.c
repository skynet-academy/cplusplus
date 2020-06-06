#include <omp.h>
#include <stdio.h>

void main() {
    long s = 0;
    long size = 1000000;

    for(int i=0; i<size; i++) {
        s = s + i;
    }

    printf("S: %ld\n", s);
}