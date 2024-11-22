/*
CHAT SERVER:UDP
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
	//sending & recieving buffers:
	char sendline[100];
	char rcvline[100];
	//exit:
	char ex[]="exit";
	//create socket:
	listen_fd=socket(AF_INET,SOCK_DGRAM,0);		//for udp use dgram
	if(listen_fd<0){
		printf("Socket creation failed");
		exit(0);
	}
	//define structure:
	struct sockaddr_in servaddr,cliaddr;
	//clear:
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(12345);
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	//bind:
	bind(listen_fd,(struct sockaddr*)&servaddr,sizeof(servaddr));
	//send/receive loop
	while(1){
		//recieve msg from client
		bzero(rcvline,sizeof(rcvline));
		recvfrom(listen_fd,rcvline,strlen(rcvline),0,(struct sockaddr*)&cliaddr,sizeof(cliaddr));
		printf("\nMessage from client: %s",rcvline);
		//compare with exit:
		if(strncmp(rcvline,ex,4)==0){
			break;
		}
		//send msg to client
		bzero(sendline,sizeof(sendline));
		fgets(sendline,100,stdin);	//take input
		sendto(listen_fd,sendline,strlen(sendline),0,(struct sockaddr*)&cliaddr,sizeof(cliaddr));
		if(strncmp(sendline,ex,4)==0){
			break;
		}
	}
	//close:
	close(listen_fd);
	return 0;
}

