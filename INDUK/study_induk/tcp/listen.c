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

	if(argc!=3) return -1;

	nPort = atoi(argv[2]);
	nFd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&sAddr, sizeof(struct sockaddr_in));
	sAddr.sin_family = PF_INET;
	sAddr.sin_addr.s_addr = inet_addr(argv[1]);
	sAddr.sin_port = htons(nPort);

	if(bind(nFd, (struct sockaddr*)&sAddr, sizeof(sAddr))<0) return -1;

	listen(nFd,10);
	getchar();
	return 0;
}

