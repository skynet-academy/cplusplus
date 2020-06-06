#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>

int main() {
	int sd;
	int reuse = 1;

	sd = socket( AF_INET, SOCK_STREAM, 0 );
	if ( setsockopt( sd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int) ) == -1 ) {
		printf("setsockopt error\n");
		return 1;
	}

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port   = htons(7777);

	struct in_addr ip_addr;
	if ( inet_pton( AF_INET, "127.0.0.1", &ip_addr) != 1 ) {
		printf("inet_pton error\n");
		return 1;
	}

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
	int client_sd = accept( sd, NULL, NULL );

	if ( client_sd == -1 ) {
		printf("accept error\n");
		return 1;
	}
	printf("accepting ok!\n");

	int i;

	char buf[100];
	while( 1 ) {
		printf("Reading from client ...\n");
		read( client_sd, buf, 100 );
		printf("Reading from client ok!\n");

		if ( strncmp( buf, "hi", 2 ) == 0 ) {
			printf("Writing to client ...\n");
			write( client_sd, "Hello\n", 6 );
			printf("Writing to client ok!\n");			
		}
		else if ( strncmp( buf, "bye", 3 ) == 0 ) {
			printf("Writing to client ...\n");
			write( client_sd, "Goodbye\n", 8 );
			printf("Writing to client ok!\n");				

			close( client_sd );
			close( sd );
			return 0;
		}
		else {
			printf("Writing to client ...\n");
			write( client_sd, "Unknown command\n", 16 );
			printf("Writing to client ok!\n");				
		}
		
	}

	close( sd );
}