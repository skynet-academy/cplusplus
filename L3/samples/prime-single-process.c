#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <math.h>

// For compilation we need to use "-lm" link option to gcc
// For example: gcc prime-single-process.c -lm && ./a.out

int is_prime_number(long n) {
    for(int i=2; i<sqrtl(n); i++) {
        if (n % i == 0) {
            return 0;
        }
    }

    return 1;
}

int main() {
    int RANGE = 10000;

    for(int i=1; i<RANGE; i++) {
        if (is_prime_number(i) == 1) {
            printf("Prime: %d\n", i);
        }
    }

    printf("Program finished\n");
}
