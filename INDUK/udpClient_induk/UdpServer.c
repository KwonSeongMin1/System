#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <poll.h>

int main(int argc, char *argv[]){

    int nSocketFd;
    char pBuffer[BUFSIZ];
    int nBufferLen;
    struct sockaddr_in stSAddr;
    struct sockaddr_in stCAddr;
	int nSAddr_size;
    int nCAddr_size;
	
	// poll
	int nRetval;
	struct pollfd rfds[2];

	rfds[0].fd=0;	// input in server
	rfds[0].events=POLLIN;	// event monitering
	rfds[0].revents=0;

    if(argc!=2){
        printf("Usage : %s <port>\n", argv[0]);
        return -1;
    }

	// make socket
    nSocketFd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	rfds[1].fd = nSocketFd;	// input in socket
	rfds[1].events = POLLIN;	// event monitering
	rfds[1].revents = 0;


    memset(&stSAddr, 0, sizeof(stSAddr));
    stSAddr.sin_family = PF_INET;	// udp
    stSAddr.sin_addr.s_addr = htonl(INADDR_ANY);	// ip
    stSAddr.sin_port = htons(atoi(argv[1]));	// port
	
	// binding
    if(bind(nSocketFd,(struct sockaddr *)&stSAddr, sizeof(stSAddr))<0){
        printf("Binding Failed.\n");
        return -1;
    }


    do{
		// start polling
		nRetval=poll(rfds,2,1000);
		if(nRetval<0) break;
		if(nRetval==0) continue;
		
		// Keyboard Input
		if(rfds[0].revents&POLLIN){
			nCAddr_size = sizeof(stCAddr);
			memset(pBuffer,0,BUFSIZ);
			nBufferLen=read(0,pBuffer,BUFSIZ);
			nBufferLen=sendto(nSocketFd,pBuffer,nBufferLen,0,(struct sockaddr *)&stCAddr,nCAddr_size);
			if(nBufferLen>0){
				printf("TX : %s",pBuffer);
				if(strncasecmp(pBuffer,"exit",4)==0) break;
			}
		}
		
		// Client Output
		if(rfds[1].revents&POLLIN){
			memset(pBuffer,0,BUFSIZ);
			nBufferLen=recvfrom(nSocketFd, pBuffer, BUFSIZ,0,(struct sockaddr *)&stCAddr,&nCAddr_size);
			if(nBufferLen>0){
				printf("---Client Information---\n");
				printf("Addr : %s\n",inet_ntoa(stCAddr.sin_addr));
				printf("Port : %d\n",ntohs(stCAddr.sin_port));
				printf("RX : %s\n",pBuffer);
				if(strncasecmp(pBuffer,"exit",4)==0) break;
			}
			else break;
		}
   } while(1);
   close(nSocketFd);
   return 0;
}
