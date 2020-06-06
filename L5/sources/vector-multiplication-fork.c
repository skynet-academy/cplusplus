#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>


void generate_vector(int *v, int size) {
    for(int i = 0; i < size; i++) {
        v[i] = rand() % 10;
    }
}

void print_vector(int *v, int size) {
    for(int i = 0; i < size; i++) {
        printf("%2d ", v[i]);
    }
    printf("\n");
}

void multiply_vectors(int *v1, int *v2, int *result, long start, long stop) {
    for(int i=start; i<stop; i++) {
        result[i] = v1[i] * v2[i];
    }
}

int main() {
    pid_t pid;
    int SIZE = 15;
    int N = 1;
    int chunk = SIZE / N;

    int *vector1;
    int *vector2;
    int *result;

    // Allocate memory
    int sm1 = shmget( IPC_PRIVATE, sizeof(int) * SIZE, 0666 | IPC_CREAT | IPC_EXCL );
    int sm2 = shmget( IPC_PRIVATE, sizeof(int) * SIZE, 0666 | IPC_CREAT | IPC_EXCL );
    int sm3 = shmget( IPC_PRIVATE, sizeof(int) * SIZE, 0666 | IPC_CREAT | IPC_EXCL );

    // Attach to the process
    vector1 = (int*)shmat(sm1, NULL, 0);
    vector2 = (int*)shmat(sm2, NULL, 0);
    result = (int*)shmat(sm3, NULL, 0);

    generate_vector(vector1, SIZE);
    generate_vector(vector2, SIZE);

    for(int i=0; i<N; i++) {
        pid = fork();
        if (pid == 0) {
            multiply_vectors(vector1, vector2, result, i*chunk, i*chunk + chunk);
            return 0;
        }
    }

    // We in parent process only
    while(wait(NULL) != -1) {};

    if (SIZE < 20) {
        print_vector(vector1, SIZE);
        print_vector(vector2, SIZE);
        print_vector(result, SIZE);
    }

    // Remove memory
    shmctl(sm1, IPC_RMID, NULL);
    shmctl(sm2, IPC_RMID, NULL);
    shmctl(sm3, IPC_RMID, NULL);
}