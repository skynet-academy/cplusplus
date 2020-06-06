#include <arpa/inet.h>
#include <stdio.h>

int main() {
    char *ip = "192.168.1.5";    
    struct in_addr ip_addr;
    char buf[INET_ADDRSTRLEN];
    int r;
    if ( (r = inet_pton( AF_INET, ip, &ip_addr)) != 1 ) {
        printf("inet_pton error\n");        
        
        if ( r == 0 ) {
            printf("inet_pton wrong address format\n");
        }
        return 1;
    }    
        
    if ( inet_ntop( AF_INET, &ip_addr, buf, INET_ADDRSTRLEN) == NULL ) {
        printf("inet_ntop error\n");
        return 1;
    }
    
    printf("%s\n", buf);
    
    return 0;
}