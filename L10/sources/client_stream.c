#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main() {
	int sd;
	int reuse = 1;

	sd = socket( AF_INET, SOCK_STREAM, 0 );

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port   = htons(7777);

	struct in_addr ip_addr;
	
	if ( inet_pton( AF_INET, "127.0.0.1", &ip_addr) != 1 ) {
		printf("inet_pton error\n");
		return 1;
	}
	
	addr.sin_addr = ip_addr;

	printf("connecting ...\n");
	if ( connect( sd, (struct sockaddr*) &addr, sizeof( addr ) ) == -1 ) {
		printf("connect error\n");
		return 1;
	} 
	printf("connecting ok!\n");

	int i;
	char buf[100];
	for( i=0; i<5; i++ ) {
		printf("writing to server: hi\n");
		write( sd, "hi", 2 );
		printf("writing to server ok!\n");

		printf("reading from server ...\n");
		read( sd, buf, 100 );
		printf("reading from server: %s\n", buf);
		sleep(3);
	}

	close( sd );

	return 0;
}