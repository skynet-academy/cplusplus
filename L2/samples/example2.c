#include <unistd.h>
#include <stdio.h>

int main() {
	pid_t pid;

	pid = fork();
	if ( pid == 0 ) {
		// Child
		printf("Child\n");
		sleep(2);
	}
	else {
		// Parent
		printf("Parent\n");
		sleep(2);
	}

	printf("Finished\n");

	return 0;

