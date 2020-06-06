#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <sys/ipc.h>
#include <sys/shm.h>

double calculate_pi(long start, long stop) {
    double s = 0;

    for(int i=start; i<stop; i++) {
        s = s + pow(-1, i+1) * 4 / (2*i - 1);
    }

    return s;
}


int main() {
	pid_t pid;
    double *shared;
    struct timeval  tv1, tv2;

    int COUNT = 100000000;
    int N = 2; // number of processes
    int size = COUNT / N;

    // Allocate memory
    int sm = shmget( IPC_PRIVATE, sizeof(double) * N, 0666 | IPC_CREAT | IPC_EXCL );
    // Attach to the process
    shared = (double*)shmat(sm, NULL, 0);


	printf("Main process, pid=%d, ppid=%d\n", getpid(), getppid());

    gettimeofday(&tv1, NULL); // Wall clock time

    for(int i=0; i<N; i++) {
        pid = fork();
        if (pid == 0) {
            // Child N
            *shared = *shared + calculate_pi(i*size + 1, i*size+size);    
            return 0;
        }
    }

    // We in parent process only
    while(wait(NULL) != -1) {};

    gettimeofday(&tv2, NULL);

    printf("Total pi=%.20f\n", *shared);
    printf ("Total time = %f seconds\n",
         (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +
         (double) (tv2.tv_sec - tv1.tv_sec));
}