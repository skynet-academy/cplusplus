#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/ipc.h>
#include <sys/shm.h>


int main() {
	pid_t pid;
    struct timeval  tv1, tv2;
    double *shared;

    int N = 3; // number of processes

    // Allocate memory
    int sm = shmget( IPC_PRIVATE, sizeof(double) * N, 0666 | IPC_CREAT | IPC_EXCL );
    // Attach to the process
    shared = (double*)shmat(sm, NULL, 0);

	printf("Main process, pid=%d, ppid=%d\n", getpid(), getppid());

    gettimeofday(&tv1, NULL); // Wall clock time

    for(int i=0; i<N; i++) {
        pid = fork();
        if (pid == 0) {
            shared[i] = i;

            printf("Worker #%d created and start processing!\n", i);            
            return 0;
        }
    }

    // We in parent process only
    while(wait(NULL) != -1) {};

    for(int i=0; i<N; i++) {
        printf("Shared %d: %f\n", i, shared[i]);
    }

    // Remove memory
    shmctl(sm, IPC_RMID, NULL);

    gettimeofday(&tv2, NULL);

    printf ("Total time = %f seconds\n",
         (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +
         (double) (tv2.tv_sec - tv1.tv_sec));
}
