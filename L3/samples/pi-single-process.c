#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <math.h>

// For compilation we need to use "-lm" link option to gcc
// For example: gcc pi-single-process.c -lm && ./a.out

double calculate_pi(long start, long stop) {
    double s = 0;

    for(int i=start; i<stop; i++) {
        s = s + pow(-1, i+1) * 4 / (2*i - 1);
    }

    return s;
}

int main() {
    int start = 1;
    int stop = 10;

    double pi = calculate_pi(start, stop);

    printf("Pi: %.10f\n", pi);
}
