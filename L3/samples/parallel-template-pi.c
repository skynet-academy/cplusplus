#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>

double calculate_pi(long start, long stop) {
    double s = 0;

    for(int i=start; i<stop; i++) {
        s = s + pow(-1, i+1) * 4 / (2*i - 1);
    }

    return s;
}


int main() {
	pid_t pid;
    struct timeval  tv1, tv2;

    int COUNT = 100000000;
    int N = 4; // number of processes
    int size = COUNT / N;

    int d[N][2];

	printf("Main process, pid=%d, ppid=%d\n", getpid(), getppid());

    gettimeofday(&tv1, NULL); // Wall clock time

    double local_sum = 0;

    for(int i=0; i<N; i++) {
        pipe(d[i]); // d[i][0] - read, d[i][1] - write

        pid = fork();
        if (pid == 0) {
            // Child N
            local_sum = local_sum + calculate_pi(i*size + 1, i*size+size);
            printf("Local sum of process %d is: %.10f \n", i, local_sum);

            write(d[i][1], &local_sum, sizeof(double));            
            return 0;
        }
    }

    double pi = 0;
    for(int i=0; i<N; i++) {
        double local;

        read(d[i][0], &local, sizeof(double));
        pi = pi + local;
    }

    // We in parent process only
    while(wait(NULL) != -1) {};

    gettimeofday(&tv2, NULL);

    printf("Total pi=%.10f\n", pi);
    printf ("Total time = %f seconds\n",
         (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +
         (double) (tv2.tv_sec - tv1.tv_sec));
}
