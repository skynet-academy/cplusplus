#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

// Add control thread

long PTHREAD_COUNT = 1;
long counter = 1;

void *worker_thread() {
    while(1) {
        counter += 1;
        sleep(1);

        // printf("Current counter: %ld\n", counter);
    }
}

void *monitor_thread() {
    long old_value = 0;
    long current_value = 0;

    while(1) {        
        sleep(5);
        current_value = counter;

        double speed = (current_value - old_value) / 5.0;
        old_value = current_value;

        printf("Speed: %f/sec\n", speed);
    }
}

int main() {
    pthread_t monitor_tid;
    pthread_t tid[50];

    int n;
    int current_threads_number = PTHREAD_COUNT;

    pthread_create (&monitor_tid, NULL, monitor_thread, NULL);   

    for(int i=0; i<PTHREAD_COUNT; i++) {
        pthread_create (&tid[i], NULL, worker_thread, NULL);      
    }

    while (1) {
        printf("Enter new thread number: \n");
        scanf("%d", &n);

        int thread_add_number = 0;
        int thread_del_number = 0;

        if (n > current_threads_number) {
            thread_add_number = n - current_threads_number;
        } else {
            thread_del_number = current_threads_number - n;
        }        

        printf("Add: %d\n", thread_add_number);
        printf("Del: %d\n", thread_del_number);

        for(int i=0; i<thread_add_number; i++) {
            // Implement code for start new threads
        }

        for(int i=0; i<thread_del_number; i++) {
            // Implement cancelation policy
        }

        current_threads_number = n;
    }

    for(int i=0; i<current_threads_number; i++) {
        pthread_join(tid[i], NULL);
    }
    
    printf("Program finished\n");
}