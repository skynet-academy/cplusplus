#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

struct Range {
    long start;
    long count;
};

int main() {
	int sd;
	int reuse = 1;
    int pid;

	sd = socket( AF_INET, SOCK_STREAM, 0 );
	if ( setsockopt( sd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int) ) == -1 ) {
		printf("setsockopt error\n");
		return 1;
	}

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port   = htons(7777);

	struct in_addr ip_addr;
	ip_addr.s_addr = INADDR_ANY;

	addr.sin_addr = ip_addr;

	printf("binding ...\n");
	if ( bind( sd, (struct sockaddr *) &addr, sizeof(addr) ) == -1 ) {
		printf("bind error\n");
		return 1;
	}
	printf("binding ok!\n");

	printf("listening ...\n");
	if ( listen( sd, 5 ) == -1 ) {
		printf("listen error\n");
		return 1;
	}
	printf("listening ok!\n");

	printf("accepting ...\n");
   
    long N = 1000000;
    for(int i=0; i<3; i++) {
        // Blocking!!!
        int client_sd = accept( sd, NULL, NULL );

        struct Range range;
        range.start = i;
        range.count = N;

        pid = fork();
        if (pid == 0) {
            write( client_sd, &range, sizeof(struct Range) );            

            // Got result from client
            double result;
            read( client_sd, &result, sizeof(double) );

            printf("Result from the client #%d is: %f\n", i, result);
            return 0;
        }
    }

	close( sd );
}