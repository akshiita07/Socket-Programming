//	MULTICAST UDP CLIENT

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
    struct ip_mreq multicast_request;
    char str[100];

    // 1. Create a UDP socket
    sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_fd < 0) {
        printf("Socket creation failed");
        exit(0);
    }

    // 2. Set SO_REUSEADDR option
    int reuse = 1;
    if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
        perror("Failed to set SO_REUSEADDR option");
        close(sock_fd);
        exit(EXIT_FAILURE);
    }

    // 3. Bind the socket to a local address
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); // Bind to all local interfaces

    bind(sock_fd, (struct sockaddr*)&servaddr, sizeof(servaddr))

    // 4. Join the multicast group
    multicast_request.imr_multiaddr.s_addr = inet_addr(MULTICAST_GROUP); // Multicast group address
    multicast_request.imr_interface.s_addr = htonl(INADDR_ANY);         // Local interface

    setsockopt(sock_fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &multicast_request, sizeof(multicast_request))

    // 5. Receive multicast messages
    while (1) {
        memset(buffer, 0, sizeof(buffer));
        ssize_t len = recvfrom(sock_fd, buffer, sizeof(buffer), 0, NULL, NULL);
        if (len < 0) {
            perror("Failed to receive multicast message");
            break;
        }

        std::cout << "Received multicast message: " << buffer << std::endl;
    }

    // Leave the multicast group
    setsockopt(sock_fd, IPPROTO_IP, IP_DROP_MEMBERSHIP, &multicast_request, sizeof(multicast_request));

    close(sock_fd);
    return 0;
}

