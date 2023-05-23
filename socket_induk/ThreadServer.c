#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>

#include "Network_Common.h"
void *KeyboardReader(void *p_nCFd);
void receiver(int nCFd);
int g_bRunning=1;

int main(int argc, char *argv[]){

	int nSFd;
	int nCFd;

	struct sockaddr_in cAddr;
	socklen_t nCAddr;

	pthread_t pthread_KeyboardReader;
	
	if(argc!=2){
		printf("Usage : %s <port>\n",argv[0]);
		return -1;
	}
	printf("Port %s\n",argv[1]);
	nSFd=start_tcp_server(atoi(argv[1]),1);
	if(nSFd>0){
		printf("TCP Server is started.\n");
	}
	else{
		printf("Starting Server is failed.\n");
		return -1;
	}
	nCFd=accept(nSFd,(struct sockaddr*)&cAddr,&nCAddr);
	if(nCFd>0){
		printf("Client Info:\n");
		printf("\t- IP Address : %s\n",inet_ntoa(cAddr.sin_addr));
		printf("\t- Port : %d\n",ntohs(cAddr.sin_port));

		pthread_create(&pthread_KeyboardReader, NULL,KeyboardReader,(void*)&nCFd);
		receiver(nCFd);
		pthread_join(pthread_KeyboardReader,NULL);
		close(nCFd);
	}
	else{
		printf("Connection Failure.\n");
	}
	close(nSFd);
	return 0;
}

void receiver(int nCFd){

	char szBuffer[BUFSIZ];
	int nLen=0;

	do{
		bzero(szBuffer,BUFSIZ);
		nLen=recv(nCFd,szBuffer,BUFSIZ,0);
		if(nLen>0){
			printf("Recv : %s",szBuffer);
		}
	}while(g_bRunning);
	printf("receiver function is finished.\n");
}
void *KeyboardReader(void *p_nCFd){
	int nCFd=*(int*)p_nCFd;
	char szBuffer[BUFSIZ];
	int nLen=0;
	while((nLen=read(0,szBuffer,BUFSIZ))>0){
		send(nCFd,szBuffer,nLen,0);
		if(strncasecmp(szBuffer,"exit",4)==0) break;
	}
	g_bRunning=0;
}

