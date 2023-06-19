#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    struct sockaddr_in serv_addr, client_addr;
    int sock;
    if ((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
        perror("socket");
        exit(1);
    }
    memset((char *) &serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8888);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    int bcMode = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &bcMode, sizeof(bcMode))) {
        perror("setsockopt()");
        exit(1);
    }
    memset((char *) &client_addr, 0, sizeof(client_addr));
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(8888);
    client_addr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
    while (1) {
        char buf[1024];
        printf("Введите сообщение : ");
        fgets(buf, 1024, stdin);
        if (sendto(sock, buf, 1024, 0, (struct sockaddr *) &client_addr, sizeof(client_addr)) == -1) {
            perror("sendto()");
            exit(1);
        }
    }
    close(sock);
    return 0;
}