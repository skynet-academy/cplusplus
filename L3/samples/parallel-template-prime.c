#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>


int is_prime_number(long n) {
    for(int i=2; i<sqrtl(n); i++) {
        if (n % i == 0) {
            return 0;
        }
    }

    return 1;
}


int main() {
	pid_t pid;
    struct timeval  tv1, tv2;

    int RANGE = 1000000;
    int N = 100; // number of processes
    int size = RANGE / N;

	printf("Main process, size=%d, N=%d\n", size, N);

    gettimeofday(&tv1, NULL); // Wall clock time

    for(int i=0; i<N; i++) {
        pid = fork();
        if (pid == 0) {
            // Search for prime numbers in the RANGE / N
            for(int k=i*size; k<i*size+size; k++) {
                if (is_prime_number(k) == 1) {
                    // printf("Prime: %d\n", k);
                }
            }
            
            return 0;
        }
    }

    // We in parent process only
    while(wait(NULL) != -1) {};

    gettimeofday(&tv2, NULL);

    printf ("Total time = %f seconds\n",
         (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +
         (double) (tv2.tv_sec - tv1.tv_sec));
}
