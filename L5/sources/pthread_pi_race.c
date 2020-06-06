#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <math.h>

#define N 4 // number of threads
const int COUNT = 100000000;
double shared[N];

struct Attrs {
    int start;
    int stop;
    int index;
};

double calculate_pi(long start, long stop) {
    double s = 0;

    for(int i=start; i<stop; i++) {
        s = s + pow(-1, i+1) * 4 / (2*i - 1);
    }

    return s;
}

void * start_thread (void *data)
{
    struct Attrs local_data = *(struct Attrs*) data;   

    double s = calculate_pi(local_data.start, local_data.stop);
    shared[local_data.index] = s;
}


int main() {
    pthread_t tid[N];
    int size = COUNT / N;

    struct timeval  tv1, tv2; 

	printf("Main process, pid=%d, ppid=%d\n", getpid(), getppid());

    gettimeofday(&tv1, NULL); // Wall clock time

    struct Attrs attrs;
    for(int i=0; i<N; i++) {
        attrs.index = i;
        attrs.start = i*size + 1;
        attrs.stop = i*size+size;
        
        pthread_create (&tid[i], NULL, start_thread, (void*) &attrs);        
    }

    for(int i=0; i<N; i++) {
        pthread_join(tid[i], NULL);
    }

    double pi = 0;
    for(int i=0; i<N; i++) {
        pi = pi + shared[i];        
    }


    gettimeofday(&tv2, NULL);

    printf("Pi: %.10f\n", pi);
    printf ("Total time = %f seconds\n",
         (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +
         (double) (tv2.tv_sec - tv1.tv_sec));
}