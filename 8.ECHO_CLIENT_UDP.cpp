/*
ECHO CLIENT:UDP
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
	struct sockaddr_in servaddr;
	//clear:
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(12345);
	servaddr.sin_addr.s_addr=inet_addr(127.0.0.1);
	
	//for length use socklen_t:
	socklen_t servaddr_Length=sizeof(servaddr);
	
	//echo:
	while(1){
		//send msg to server & it will echo back:
		bzero(str,sizeof(str));
		fgets(str,sizeof(str),stdin);
		sendto(sock_fd,str,sizeof(str),0,(struct sockaddr*)&servaddr,servaddr_Length);
		recvfrom(sock_fd,str,sizeof(str),0,(struct sockaddr*)&servaddr,servaddr_Length);
		printf("Server echo: %s",str);
	}
	close(sock_fd);
	
	return 0;
}

