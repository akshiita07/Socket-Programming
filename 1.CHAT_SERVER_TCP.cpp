/*
CHAT SERVER:TCP
*/

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<string.h>
#include<unistd.h>

int main()
{
	//file descriptors
	int listen_fd;		//for socket
	int comm_fd;		//for accept
	//sending & recieving buffers:
	char sendline[100];
	char rcvline[100];
	//exit:
	char ex[]="exit";
	//create socket:
	listen_fd=socket(AF_INET,SOCK_STREAM,0);
	//define structure:
	struct sockaddr_in servaddr;
	//clear:
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(12345);
	servaddr.sin_addr.s_addr=INADDR_ANY;
	//bind:
	bind(listen_fd,(struct sockaddr*)&servaddr,sizeof(servaddr));
	//listen:
	listen(listen_fd,10);
	//accept:
	comm_fd=accept(listen_fd,(struct sockaddr*)NULL,NULL);
	//send/receive loop
	while(1){
		//recieve msg from client
		bzero(rcvline,sizeof(rcvline));
		recv(comm_fd,rcvline,strlen(rcvline),0);
		printf("\nMessage from client: %s",rcvline);
		//compare with exit:
		if(strncmp(rcvline,ex,4)==0){
			break;
		}
		//send msg to client
		bzero(sendline,sizeof(sendline));
		fgets(sendline,100,stdin);	//take input
		send(comm_fd,sendline,strlen(sendline),0);
		if(strncmp(sendline,ex,4)==0){
			break;
		}
	}
	//close:
	close(listen_fd);
	close(comm_fd);
	return 0;
}

