#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <pthread.h>

short shared_var = 0;

void * thread_func(void *arg)
{ 
	shared_var = shared_var + 1;
    printf("Shared var in thread N%ld: %d\n", pthread_self(), shared_var);

    sleep(1);
}

int main(int argc, char * argv[])
{ 
	int id1, id2, result;
	pthread_t thread1, thread2;
	
	result = pthread_create(&thread1, NULL, thread_func, NULL);
	result = pthread_create(&thread2, NULL, thread_func, NULL);

	// Wait while threads are finished
	result = pthread_join(thread1, NULL);
	result = pthread_join(thread2, NULL);

	printf("Shared var in main thread: %d\n", shared_var);
}