#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

pthread_mutex_t lock;
long counter = 1;
long current_prime = 0;
long prime_count = 0;
long target_prime_position = 7; // 12009;

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

void *find_prime_thread() {
    while(1) {
        if (is_prime_number(counter) == 1) {
            current_prime = counter;
            prime_count += 1;
        }
        counter += 1;
    }
    pthread_exit(NULL);
}

void *check_current_thread() {
    while(1) {
        printf("Prime count: %ld\n", prime_count);
        if (prime_count == target_prime_position) {
            printf("Found %ld prime number: %ld\n", prime_count, current_prime);
            pthread_exit(NULL);
        }
    }
}

int main() {
    pthread_t tid1, tid2;

    pthread_create (&tid1, NULL, find_prime_thread, NULL);      
    pthread_create (&tid2, NULL, check_current_thread, NULL);      

    pthread_join(tid2, NULL);
    printf("Program finished\n");
}