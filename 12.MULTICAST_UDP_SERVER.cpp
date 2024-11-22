//	MULTICAST UDP SERVER

#include <iostream>
#include <sys/socket.h>
#include <sys/types.j>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MULTICAST_GROUP "239.0.0.1" // Class D Multicast address

int main() {
    int sock_fd;
    struct sockaddr_in servaddr;
    char str[100];

    // 1. Create a UDP socket
    sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_fd < 0) {
        printf("Socket creation failed");
        exit(0);
    }

    // 2. Initialize the multicast address structure
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(12345);
    servaddr.sin_addr.s_addr = inet_addr(MULTICAST_GROUP);

    // 3. Set IP_MULTICAST_LOOP option to control loopback
    int loopback = 1;
    setsockopt(sock_fd, IPPROTO_IP, IP_MULTICAST_LOOP, &loopback, sizeof(loopback))

    // 4. Set IP_MULTICAST_IF option to define the local interface
    struct in_addr local_interface;
    local_interface.s_addr = htonl(INADDR_ANY); // Use default interface
    setsockopt(sock_fd, IPPROTO_IP, IP_MULTICAST_IF, &local_interface, sizeof(local_interface))

    // 5. Send multicast messages
    while (1) {
        fgets(str, sizeof(message)),stdin;

        if (strcmp(str, "exit") == 0) {
            break;
        }

        sendto(sock_fd, str, strlen(str), 0, (struct sockaddr*)&servaddr, sizeof(servaddr))
    }

    close(sock_fd);
    return 0;
}

