/*
ECHO SERVER:TCP
jo msg client sends server just echoes it back
server's purpose is to receive a message from the client and immediately send the exact same message back to the client
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
	int comm_fd;
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
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	//bind:
	bind(listen_fd,(struct sockaddr*)&servaddr,sizeof(servaddr));
	//listen:
	listen(listen_fd,10);
	//accept:
	comm_fd=accept(listen_fd,(struct sockaddr*)NULL,NULL);
	//echo:
	while(1){
		//recieve msg from client & echo it back:
		bzero(str,sizeof(str));
		recv(comm_fd,str,sizeof(str),0);
		printf("server echoing back: ");
		send(comm_fd,str,sizeof(str),0);
	}
	close(listen_fd);
	close(comm_fd);

	return 0;
}

