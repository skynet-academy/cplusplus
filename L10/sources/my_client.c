#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <math.h>

struct Range {
    long start;
    long count;
};

double calculate_pi(long start, long stop) {
    double s = 0;

    for(int i=start; i<stop; i++) {
        s = s + pow(-1, i+1) * 4 / (2*i - 1);
    }

    return s;
}

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

    // Get range from server
    struct Range range;

    read(sd, &range, sizeof(struct Range));
    printf("Range from server is: %ld, %ld\n", range.start, range.count);

    // Pi computation in Range
    double result = calculate_pi(range.start * range.count +1, range.start * range.count + range.count);
    write(sd, &result, sizeof(double));

	close( sd );

	return 0;
}