/*
TO DETERMINE IF COMPUTER STORES BYTES IN LITTLE ENDIAN OR BIG ENDIAN
*/

#include<iostream>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#inlcude<stdlib.h>
#include<stdio.h>
#include<arpa/inet.h>
#include<netinet/in.h>

int main()
{
	union{
		short s;
		char c[sizeof(short)];
	}un;
	
	un.s=0x0102;
	
	if(sizeof(short==2)){
		
		if(un.c[0]==1 && un.c[1]==2){
			printf("Big endian");
		}else if(un.c[0]==2 && un.c[1]==1){
			printf("Little endian");
		}else{
			printf("Unknown");
		}
		
	}else{
		printf("Size of short is: %d",sizeof(short));
	}

	return 0;
}

