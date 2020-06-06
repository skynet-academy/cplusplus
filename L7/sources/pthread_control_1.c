#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

// Naive approach
// What problems here?

long PTHREAD_COUNT = 4;
long counter = 1;

void *worker_thread() {
    while(1) {
        counter += 1;
        sleep(1);

        printf("Current counter: %ld\n", counter);
    }
}

void *monitor_thread() {
    long old_value = 0;
    long current_value = 0;

    while(1) {        
        sleep(5);
        current_value = counter;

        double speed = (current_value - old_value) / 5;
        old_value = current_value;

        printf("Speed: %f/sec\n", speed);
    }
}

int main() {
    pthread_t monitor_tid;
    pthread_t tid[PTHREAD_COUNT];

    pthread_create (&monitor_tid, NULL, monitor_thread, NULL);   

    for(int i=0; i<PTHREAD_COUNT; i++) {
        pthread_create (&tid[i], NULL, worker_thread, NULL);      
    }

    for(int i=0; i<PTHREAD_COUNT; i++) {
        pthread_join(tid[i], NULL);
    }
    
    printf("Program finished\n");
}