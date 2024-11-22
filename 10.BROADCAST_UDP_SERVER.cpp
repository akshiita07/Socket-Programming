/*
BROADCAST UDP SERVER
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
#efine BROADCAST_ADDRESS "255.255.255.255"

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
	//SET FOR BROADCAST:
	int broadcast=1;
	setsockopt(sock_fd,SOL_SOCKET,SO_BROADCAST,&broadcast,sizeof(broadcast));
	//structure:
	struct sockaddr_in servaddr,cliaddr;
	bzero(&servaddr,sizeof(servaddr))
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(12345);
	servaddr.sin_addr.s_addr=inet_addr(BROADCAST_ADDRESS);
	//sending so no bind reqd
	socklen_t cliLength=sizeof(cliaddr);
	//sent broadcast msg:
	while(1){
		bzero(str,sizeof(str));
		fgets(str,sizeof(str),stdin);
		sendto(sock_fd,str,sizeof(str),0,(struct sockaddr*)&cliaddr,cliLength);
		printf("Broadcasted message: %s",str);
	}
	close(sock_fd);


	return 0;
}

