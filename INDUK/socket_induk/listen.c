#include <unistd.h>
#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]){
	int nFd;
	uint16_t nPort;
	struct sockaddr_in sAddr;

	//argument error
	if(argc!=3){
		printf("usage: %s <ip> <port>\n", argv[0]);
		return -1;
	}

	nPort=atoi(argv[2]);	// string to int
	printf("IP Address : %s\n", argv[1]);
	printf("Port %d\n", nPort);
	nFd=socket(AF_INET, SOCK_STREAM,0);	//socket(IPv4, TCP, protocol value)
	printf("Server FD : %d.\n",nFd);

	bzero(&sAddr, sizeof(struct sockaddr_in));
	sAddr.sin_family=PF_INET;
	sAddr.sin_addr.s_addr=inet_addr(argv[1]);
	sAddr.sin_port=htons(nPort);

	if(bind(nFd,(struct sockaddr*)&sAddr,sizeof(sAddr))<0){
		printf("Binding Failed...\n");
		return -1;
	}

	listen(nFd,10);
	printf("listening is OK, now.\n");

	printf("Input Enter Key to finish.\n");
	getchar();
	close(nFd);
	return 0;
}

