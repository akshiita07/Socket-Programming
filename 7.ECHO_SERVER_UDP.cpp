/*
ECHO SERVER:UDP
*/

#include<iostream>
#include<stdio.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<netdb.h>
#include<string.h>

int main()
{
	//file descriptor:
	int sock_fd;
	//string
	char str[100];
	//socket:
	sock_fd=socket(AF_INET,SOCK_DGRAM,0);
	if(sock_fd<0){
		printf("Error creating socket");
		exit(0);
	}
	//str:
	struct sockaddr_in servaddr,cliaddr;
	//clear:
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(12345);
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	//bind:
	bind(sock_fd,(struct sockaddr*)&servaddr,sizeof(servaddr));
	
	
	//for length use socklen_t:
	socklen_t cliddr_Length=sizeof(cliaddr);
	
	//echo:
	while(1){
		//receive msg from client & simply echo back:
		bzero(str,sizeof(str));
		recvfrom(sock_fd,str,sizeof(str),0,(struct sockaddr*)&cliaddr,cliddr_Length);
		printf("Echoing back");
		sendto(sock_fd,str,sizeof(str),0,(struct sockaddr*)&cliaddr,cliddr_Length);
	}
	close(sock_fd);
	
	return 0;
}

