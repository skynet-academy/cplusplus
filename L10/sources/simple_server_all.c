#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

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
	/*
	if ( inet_pton( AF_INET, "192.168.0.103", &ip_addr) != 1 ) {
		printf("inet_pton error\n");
		return 1;
	}
	*/
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
	int client_sd = accept( sd, NULL, NULL );

	if ( client_sd == -1 ) {
		printf("accept error\n");
		return 1;
	}
	printf("accepting ok!\n");

	sleep(3);

	close( sd );
}