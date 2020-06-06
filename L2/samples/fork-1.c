#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main() {
	pid_t pid_1, pid_2;

	printf("Parent, pid=%d, ppid=%d\n", getpid(), getppid());

	pid_1 = fork();
	if ( pid_1 == 0 ) {
		// Child
		printf("Child 1, pid=%d, ppid=%d\n", getpid(), getppid());

		pid_2 = fork();
		if ( pid_2 == 0 ) {
			// Child
			printf("Child 2, pid=%d, ppid=%d\n", getpid(), getppid());
			return 0;
		}
		else {
			// Parent - child 1
			wait(NULL);
		}

		return 0;
			
	}
	else {
		// Parent
		wait(NULL);
	}
}
