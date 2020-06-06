#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>

int main() {
	int sd;
	
	sd = socket( AF_INET, SOCK_DGRAM, 0 );
	
	struct sockaddr_in addr, client_addr;
	int client_size = sizeof( client_addr );

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
	
	int i;

	char buf[100];


	while( 1 ) {
		printf("Reading from client ...\n");

		memset(buf, '\0', 100);

		//read( sd, buf, 100 );
		recvfrom( sd, buf, 100, 0, (struct sockaddr *) &client_addr, &client_size );

		printf("Reading from client: %s!\n", buf);

		
		if ( strncmp( buf, "hi", 2 ) == 0 ) {
			printf("Writing to client ...\n");
			sendto( sd, "Hello\n", 6, 0, (struct sockaddr *) &client_addr, client_size);
			//write( sd, "Hello\n", 6 );
			printf("Writing to client ok!\n");			
		}
		else if ( strncmp( buf, "bye", 3 ) == 0 ) {
			printf("Writing to client ...\n");
			sendto( sd, "Goodbye\n", 8, 0, (struct sockaddr *) &client_addr, client_size);
			//write( sd, "Goodbye\n", 8 );
			printf("Writing to client ok!\n");				

			close( sd );
			return 0;
		}
		else {
			printf("Writing to client ...\n");
			sendto( sd, "Unknown command\n", 16, 0, (struct sockaddr *) &client_addr, client_size);
			//write( sd, "Unknown command\n", 16 );
			printf("Writing to client ok!\n");				
		}
		
		
	}

	close( sd );
}