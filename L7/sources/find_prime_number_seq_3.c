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
long target_prime_position = 150000; // 150000; // 12009;

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
        pthread_mutex_lock(&lock); 

        if (is_prime_number(counter) == 1) {            
            prime_count += 1;

            if (prime_count == target_prime_position) {
                current_prime = counter;

                pthread_mutex_unlock(&lock); 
                pthread_exit(NULL);
            }
        }
        counter += 1;

        pthread_mutex_unlock(&lock); 
    }
    pthread_exit(NULL);
}

void *check_current_thread() {
    while(1) {
        pthread_mutex_lock(&lock); 

        if (prime_count % 1000 == 0) {
            // printf("Prime progress: %ld\n", prime_count);
        }
        
        if (current_prime != 0) {
            printf("Found %ld prime number: %ld\n", prime_count, current_prime);
            pthread_exit(NULL);
        }
        
        pthread_mutex_unlock(&lock); 
    }
}

int main() {
    pthread_t tid1, tid2;

    pthread_mutex_init(&lock, NULL);

    pthread_create (&tid1, NULL, find_prime_thread, NULL);      
    pthread_create (&tid2, NULL, check_current_thread, NULL);      

    pthread_join(tid2, NULL);
    printf("Program finished\n");
}