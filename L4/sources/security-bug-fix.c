#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>


struct User {
    long id;
    long role_id;
};

int main() {
	pid_t pid;
    struct User *shared;
    struct sembuf sem_struct;

    struct User user1;
    struct User user2;
    struct User *current_user;

    user1.id = 1;
    user1.role_id = 1;

    user2.id = 2;
    user2.role_id = 2;

    int N = 5; // number of processes
    int TRY_COUNT = 9000;

    // Allocate memory
    int sm = shmget( IPC_PRIVATE, sizeof(struct User) * 2, 0666 | IPC_CREAT | IPC_EXCL );
    // Attach to the process
    shared = (struct User*)shmat(sm, NULL, 0);

    shared[0] = user1;
    shared[1] = user2;

    // Create semaphore
    int sem_id = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);
    // set operation type
    sem_struct.sem_num = 0; 
    sem_struct.sem_op = 1;
    sem_struct.sem_flg = 0;

    // Initialize semaphore
    semop(sem_id, &sem_struct, 1);
    
	printf("Main process, pid=%d, ppid=%d\n", getpid(), getppid());

    for(int i=0; i<N; i++) {
        pid = fork();
        if (pid == 0) {                        
            current_user = &shared[1];
            
            for(int k=0; k<TRY_COUNT; k++) {
                sem_struct.sem_op = -1;
                semop(sem_id, &sem_struct, 1);
                 
                if ((*current_user).role_id == 1 && (*current_user).id != 1) {
                    printf("Access granted to user: %ld!\n", (*current_user).id);            
                }

                sem_struct.sem_op = 1;
                semop(sem_id, &sem_struct, 1);
            }

            // printf("Worker #%d finished!\n", i);            
            return 0;
        }
    }

    for(int i=0; i<100000; i++) {

        sem_struct.sem_op = -1;
        semop(sem_id, &sem_struct, 1);

        struct User tmp;
        tmp = shared[0];
        shared[0] = shared[1];
        shared[1] = tmp;

        sem_struct.sem_op = 1;
        semop(sem_id, &sem_struct, 1);
    }

    // We in parent process only
    while(wait(NULL) != -1) {};

    // Remove memory
    shmctl(sm, IPC_RMID, NULL);
    semctl(sem_id, 0, IPC_RMID, NULL);
}