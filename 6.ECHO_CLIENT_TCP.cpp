/*
ECHO CLIENT:TCP
*/

#include<iostream>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<netdb.h>

int main()
{
	//file descriptors:
	int listen_fd;
	//send & recieve
	char str[100];
	//create socket:
	listen_fd=socket(AF_INET,SOCK_STREAM,0);
	//error:
	if(listen_fd<0){
		printf("Error creating socket");
		exit(0);
	}
	//struct:
	struct sockaddr_in servaddr;
	//bzero:
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(12345);
	servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	//connect:
	connect(listen_fd,(struct sockaddr*)servaddr,sizeof(servaddr));
	//echo:
	while(1){
		//send msg to server & see what it echoes:
		bzero(str,sizeof(str));
		fgets(str,sizeof(str),stdin);
		send(listen_fd,str,sizeof(str),0);
		recv(listen_fd,str,sizeof(str),0);
		printf("server sent: %s",str);
	}
	close(listen_fd);

	return 0;
}

