#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>


int main() {
	pid_t pid_1, pid_2;

	printf("Parent, pid=%d, ppid=%d\n", getpid(), getppid());

	pid_1 = fork();

	if ( pid_1 == 0 ) {
		// Child 1

		printf("Child 1, pid=%d, ppid=%d\n", getpid(), getppid());
		return 0;			
	}
	else {
		// Parent

		pid_2 = fork();
		if ( pid_2 == 0 ) {
			// Child 2
			printf("Child 2, pid=%d, ppid=%d\n", getpid(), getppid());
			exit(0);
		}
		else {
			// Parent wait for all childs
			// wait(NULL);
			// wait(NULL);
			while(wait(NULL) != -1) {}
		}				
	}

	printf("Program finished\n");
}
