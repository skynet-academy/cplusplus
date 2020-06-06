#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/time.h>


int main() {
	pid_t pid;
    struct timeval  tv1, tv2;

    int N = 3; // number of processes

	printf("Main process, pid=%d, ppid=%d\n", getpid(), getppid());

    gettimeofday(&tv1, NULL); // Wall clock time

    for(int i=0; i<N; i++) {
        pid = fork();
        if (pid == 0) {
            printf("Worker #%d created and start processing!\n", i);

            sleep(5);
            
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
