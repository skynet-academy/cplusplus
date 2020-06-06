#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <math.h>

short shared_var = 0;

void * thread_func(void *arg)
{ 
    long n = *(long*) arg;
	double sq = sqrt(n);
    sleep(10);

    printf("SQRT of %ld is %f\n", n, sq);

    return 0;
}

int main(int argc, char * argv[])
{ 
	int id1, id2, result;
    long n;
	pthread_t thread1, thread2;

    while(1) {
        printf("Enter the number: \n");
        scanf("%ld", &n);

        result = pthread_create(&thread1, NULL, thread_func, &n);
    }
}