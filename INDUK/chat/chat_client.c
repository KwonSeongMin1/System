#include <stdio.h>
#include <stdlib.h>
#include <sys/poll.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <time.h>
#include <unistd.h>
#include "Network_Common.h"

int main(int argc,char *argv[]){
    struct sockaddr_in stCAddr;
    socklen_t nCAddr;
    struct pollfd rfds[2];
    int nTimeout=0;
    int nRetval;

	// 파일 디스크립터 초기화
    for(int i=0;i<2;i++){
        rfds[i].fd=-1;
        rfds[i].events=0;
        rfds[i].revents=0;
    }

    if(argc!=3){
        printf("Usage : %s <IP> <Port>\n",argv[0]);
        return -1;
    }

	
    printf("IP %s\n",argv[1]);
    printf("Port %s\n",argv[2]);

	// 표준 입력을 FD 0에 할당
    rfds[0].fd=0;
    rfds[0].events=POLLIN;
    rfds[0].revents=0;

	// TCP 서버 연결 시도, FD에 할당
    rfds[1].fd=connect_to_tcp_server(argv[1],atoi(argv[2]));
	// 실패 시
    if(rfds[1].fd<0){
        printf("Connecting Server is failed.\n");
        return -1;
    }
    rfds[1].events=POLLIN;
    rfds[1].revents=0;
    nTimeout=1000;

    do{
		// poll 함수 사용해 이벤트 모니터링
        nRetval=poll(rfds,2,nTimeout);
        if(nRetval>0){
			// FD에 이벤트가 발생 시
            if(rfds[0].revents&POLLIN){
				// 표준 입력을 읽어와 서버에 전송
                char strBuffer[BUFSIZ];
                int nBufferLen=0;
                bzero(strBuffer,BUFSIZ);
                nBufferLen=read(0,strBuffer,BUFSIZ);
                printf("Input : %s",strBuffer);
                if(nBufferLen>0){
                    if(strncasecmp(strBuffer,"exit",4)==0) break;
					// 서버로 데이터 전송
                    send(rfds[1].fd,strBuffer,nBufferLen,0);
                }
            }
       
         if(rfds[1].revents&POLLIN){
			 // 서버로 데이터 읽어와 출력
            char strBuffer[BUFSIZ];
            int nBufferLen=0;
            bzero(strBuffer,BUFSIZ);
            nBufferLen=read(rfds[1].fd,strBuffer,BUFSIZ);
            printf("%s",strBuffer);
        }
        else if(nRetval<0) break;
    }
    }while(1);
	// 연결된 소켓 닫기
    close(rfds[1].fd);
    printf("Bye~\n");
    return 0;
}
