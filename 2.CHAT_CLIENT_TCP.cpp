/*
CHAT CLIENT:TCP
*/

#include<iostream>
#include<sys/socket.h>
#include<sys/types.h>
#include<stdlib.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdio.h>

int main()
{
	//socket file descriptors
	int sock_fd;
	//send & receive buffers
	char sendline[100];
	char rcvline[100];
	//exit character
	char ex[]="exit";
	//socket:
	sock_fd=socket(AF_INET,SOCK_STREAM,0);
	//structure:
	struct sockaddr_in servaddr;
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(12345);
	servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");		//change is here!!
	//connect
	connect(sock_fd,(struct sockaddr*)&servaddr,sizeof(servaddr));
	//send & recive
	while(1){
		//send to server
		bzero(sendline,sizeof(sendline));
		fgets(sendline,100,stdin);
		send(sock_fd,sendline,strlen(sendline),0);
		if(strncmp(sendline,ex,4)==0){
			break;
		}
		//recieve from server
		bzero(rcvline,sizeof(rcvline));
		recv(sock_fd,rcvline,strlen(rcvline),0);
		printf("\nMessage from server: %s",rcvline);
		if(strncmp(rcvline,ex,4)==0){
			break;
		}
	}
	//close
	close(sock_fd);
	return 0;
}

