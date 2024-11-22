/*
BROADCAST UDP CLIENT
*/

#include<iostream>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	//file descriptors:
	int sock_fd;
	//	string
	char str[100];
	//socket:
	sock_fd=socket(AF_INET,SOCK_DGRAM,0);
	if(sock_fd<0){
		printf("Error creating socket");
		exit(0);
	}
	//SET FOR REUSE ADDR AS SERVER BROADCASTS:
	int reuse=1;
	setsockopt(sock_fd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(reuse));
	//structure:
	struct sockaddr_in servaddr;
	bzero(&servaddr,sizeof(servaddr))
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(12345);
	servaddr.sin_addr.s_addr=inet_addr("255.255.255.255");		//for broadcast
	
	//bind:as recv
	bind(sock_fd,(struct sockaddr*)&servaddr,sizeof(servaddr));
	
	socklen_t servLength=sizeof(servaddr);
	//sent broadcast msg:
	while(1){
		recvfrom(sock_fd,str,sizeof(str),0,(struct sockaddr*)&servaddr,servLength);
		printf("Broadcast message received: %s",str);
		bzero(str,sizeof(str));
	}
	close(sock_fd);


	return 0;
}

