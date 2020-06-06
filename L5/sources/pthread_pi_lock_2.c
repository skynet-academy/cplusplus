#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <math.h>

#define N 2 // number of threads
const int COUNT = 100000000;
double shared;

pthread_mutex_t lock;

struct Attrs {
    int start;
    int stop;
    int index;
};

double calculate_pi(long start, long stop) {
    for(int i=start; i<stop; i++) {
        pthread_mutex_lock(&lock); 
        shared = shared + pow(-1, i+1) * 4 / (2*i - 1);
        pthread_mutex_unlock(&lock); 
    }
}

void * start_thread (void *data)
{
    struct Attrs local_data = *(struct Attrs*) data;   
    free(data);

    calculate_pi(local_data.start, local_data.stop);    
}


int main() {
    pthread_t tid[N];
    pthread_mutex_init(&lock, NULL);

    int size = COUNT / N;
    
    struct timeval  tv1, tv2; 

	printf("Main process, pid=%d, ppid=%d\n", getpid(), getppid());

    gettimeofday(&tv1, NULL); // Wall clock time

    for(int i=0; i<N; i++) {
        struct Attrs *attrs = (struct Attrs*)malloc(sizeof(struct Attrs));
        attrs->index = i;
        attrs->start = i*size + 1;
        attrs->stop = i*size+size;
        
        pthread_create (&tid[i], NULL, start_thread, (void*) attrs);        
    }

    for(int i=0; i<N; i++) {
        pthread_join(tid[i], NULL);
    }

    gettimeofday(&tv2, NULL);

    printf("Pi: %.20f\n", shared);
    printf ("Total time = %f seconds\n",
         (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +
         (double) (tv2.tv_sec - tv1.tv_sec));

    pthread_mutex_destroy(&lock); 
}