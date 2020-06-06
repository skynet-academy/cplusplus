#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

// How to measure the speed of calculations (how fast counter is increasing)?

long PTHREAD_COUNT = 4;
long counter = 1;

void *worker_thread() {
    while(1) {
        counter += 1;
        sleep(1);

        printf("Current counter: %ld\n", counter);
    }
}

int main() {
    pthread_t tid[PTHREAD_COUNT];

    for(int i=0; i<PTHREAD_COUNT; i++) {
        pthread_create (&tid[i], NULL, worker_thread, NULL);      
    }

    for(int i=0; i<PTHREAD_COUNT; i++) {
        pthread_join(tid[i], NULL);
    }
    
    printf("Program finished\n");
}