#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
    struct sockaddr_in client_addr, serv_addr;
    int s;
    if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
        perror("socket");
        exit(1);
    }
    memset((char *) &client_addr, 0, sizeof(client_addr));
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(8888);
    client_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(s, (struct sockaddr *) &client_addr, sizeof(client_addr)) == -1) {
        perror("bind");
        exit(1);
    }
    while (1) {
        char buffer[1024];
        socklen_t len = sizeof(serv_addr);
        if (recvfrom(s, buffer, 1024, 0, (struct sockaddr *) &serv_addr, &len) == -1) {
            perror("recvfrom");
            exit(1);
        }
        puts(buffer);
    }
    close(s);
    return 0;
}