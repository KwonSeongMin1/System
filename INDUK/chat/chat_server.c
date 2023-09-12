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
#define MAX_CLIENTS 10

int main(int argc, char *argv[]){
    struct sockaddr_in stCAddr;
    socklen_t nCAddr;
    struct pollfd rfds[MAX_CLIENTS+2];
    int nTimeout=0;
    int nRetval;
    int nKeepRunning=1;

	// 파일 디스크립터 초기화
    for(int i=0;i<MAX_CLIENTS+2;i++){
        rfds[i].fd=-1;
        rfds[i].events=0;
        rfds[i].revents=0;
    }
	
    if(argc!=3){
        printf("Usage : %s <port> <queue>\n",argv[0]);
        return -1;
    }
	
    printf("Port %s\n",argv[1]);
    printf("Queue %s\n", argv[2]);

    if(atoi(argv[2])>MAX_CLIENTS) return -1;

	// 표준 입력을 FD 0에 할당
    rfds[0].fd=0;
    rfds[0].events=POLLIN;
    rfds[0].revents=0;

	// TCP 서버 소켓 생성 & FD 1 에 할당 
    rfds[1].fd=start_tcp_server(atoi(argv[1]),atoi(argv[2]));
    if(rfds[1].fd<0){
        printf("Starting Server is failed.\n");
        return -1;
    }
    rfds[1].events=POLLIN;
    rfds[1].revents=0;
    nTimeout=1000;
    do{
		// poll 함수로 이벤트 모니터링
        nRetval=poll(rfds,MAX_CLIENTS+2,nTimeout);
        if(nRetval>0){
            for(int i=0;i<MAX_CLIENTS+2;i++){
                if(rfds[i].fd<0) continue;
                if(rfds[i].revents&POLLIN){
                    if(i==0){
						// 입력 처리부분
                        char strBuffer[BUFSIZ];
                        int nBufferLen=0;
                        char strBuffer2[BUFSIZ];
                        int nBufferLen2=0;
                        bzero(strBuffer,BUFSIZ);
                        bzero(strBuffer,BUFSIZ);
                        nBufferLen=read(0,strBuffer,BUFSIZ);
                        printf("Input : %s",strBuffer);
                        if(nBufferLen>0){
                            if(strncasecmp(strBuffer,"exit",4)==0){
                                nKeepRunning=0;
                                break;
                            }
                            nBufferLen2=sprintf(strBuffer2,"[Server] %s",strBuffer);
                            for(int i=2;i<MAX_CLIENTS+2;i++){
                                if(rfds[i].fd<0) continue;
                                send(rfds[i].fd,strBuffer2,nBufferLen2,0);
                            }
                        }
                    }
                    else if(i==1){
						// 클라이언트 연결 요청 수락
                        printf("Connecting...");
                        int fd=accept(rfds[i].fd,(struct sockaddr*)&stCAddr,&nCAddr);
                        if(fd>0){
                            for(int i=2;i<MAX_CLIENTS+2;i++){
                                if(rfds[i].fd<0){
                                    rfds[i].fd=fd;
                                    rfds[i].events=POLLIN;
                                    rfds[i].revents=0;
                                    char strBuffer[BUFSIZ];
                                    int nBufferLen=0;
                                    bzero(strBuffer,BUFSIZ);
                                    nBufferLen=sprintf(strBuffer,"[%d] Your ID is [%d]\n", fd,fd);
                                    send(rfds[i].fd,strBuffer,nBufferLen,0);
                                    break;
                                }
                            }
                            printf("Success!!");
                        }
                        printf("\n");
                    }
                    else{
						// 클라이언트 통신 처리
                        char strBuffer[BUFSIZ];
                        int nBufferLen=0;
                        bzero(strBuffer,BUFSIZ);
                        nBufferLen=read(rfds[i].fd,strBuffer,BUFSIZ);
						
						// 클라이언트 연결 끊김 처리
                        if(nBufferLen<=0){
                            printf("A Client(%d) is disconnected.\n",rfds[i].fd);
                            close(rfds[i].fd);
                            rfds[i].fd=-1;
                            rfds[i].events=0;
                            rfds[i].revents=0;
                        }
                        else{
							// 클라이언트로부터 받은 데이터를 다른 클라이언트에게 브로드캐스팅 
                            char strBuffer2[BUFSIZ];
                            int nBufferLen2=0;
                            bzero(strBuffer2,BUFSIZ);
                            nBufferLen2=sprintf(strBuffer2,"[%d] %s",rfds[i].fd,strBuffer);
                            printf("%s",strBuffer2);
                            for(int i=2;i<MAX_CLIENTS+2;i++){
                                if(rfds[i].fd<0) continue;
                                send(rfds[i].fd,strBuffer2,nBufferLen2,0);
                            }
                        }
                    }
                }
            }
            if(nKeepRunning==0) break;
            else if(nRetval<0) break;
        }
    }while(1);

		// 열린 파일 디스크립터 닫음
        for(int i=0;i<MAX_CLIENTS+2;i++){
            if(rfds[i].fd>0) close(rfds[i].fd);
        }
        printf("Bye~\n");
        return 0;
    }

