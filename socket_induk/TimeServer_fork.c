#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <time.h>

#include "Network_Common.h"
int sending_time_info(int nCFd);
int main(int argc, char *argv[]){
	
	int nSFd;
	int nCFd;

	struct sockaddr_in cAddr;
	socklen_t nCAddr;
	if(argc!=2){
		printf("usage : %s <port>\n",argv[0]);
		return -1;
	}

	printf("Port %s\n", argv[1]);
	nSFd=start_tcp_server(atoi(argv[1]),10);
	if(nSFd>0) printf("TCP Server is started.\n");
	else{
		printf("Starting Server is failed.\n");
		return -1;
	}
	do{
	nCFd=accept(nSFd,(struct sockaddr*)&cAddr, &nCAddr);
	if(nCFd>0){
		printf("Client Info:\n");
		printf("\t- IP Address : %s\n",inet_ntoa(cAddr.sin_addr));
		printf("\t- Port : %d\n",ntohs(cAddr.sin_port));

		sending_time_info(nCFd);
		close(nCFd);
	}
	else{
		printf("Connection Failure.\n");
	}
	}while(1);
	wait(NULL);
	return 0;
}

int sending_time_info(int nCFd){
	
	char strBuffer[BUFSIZ];
	int nBufferLen=0;
	for(int i=0;i<10;i++){
		struct timeval stTimeval;
		struct tm stTm;
		gettimeofday(&stTimeval,0);
		localtime_r(&stTimeval.tv_sec,&stTm);
		nBufferLen=sprintf(strBuffer,"%04d/%02d/%02d %02d:%02d:%02d.%03d\n",
				stTm.tm_year + 1900,
				stTm.tm_mon + 1,
				stTm.tm_mday+1,
				stTm.tm_hour,
				stTm.tm_min,
				stTm.tm_sec,
				stTimeval.tv_usec/1000);
		send(nCFd, strBuffer,nBufferLen,0);
		sleep(1);
	}
	return 0;
}

