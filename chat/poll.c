#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <poll.h>
#include <unistd.h>
#include <time.h>
#define MAX_FDS 10

int main(void){

    int nRetval=0;
    char szBuffer[BUFSIZ];
    int nBufferLen=0;
    struct pollfd fds[MAX_FDS];
    time_t nPrevTime=0;
    time_t nCurTime=0;

	// fds 배열 초기화
    for(int i=0;i<MAX_FDS;i++){
        fds[i].fd=-1;
        fds[i].events=0x00;
        fds[i].revents=0x00;
    }

    fds[0].fd=0;	// 표준 입력 파일 디스크립터 설정
    fds[0].events=POLLIN;	// 입력 이벤트 모니터링 설정
    fds[0].revents=0;
    time(&nPrevTime);	// 이전 시간 설정
		
    do{	// 무한 루프
        nRetval=poll(fds,1,5000);	// 입력 대기

        if(nRetval>0){
            time(&nPrevTime);	// 이전 시간 갱신
            if(fds[0].revents&POLLIN){
                bzero(szBuffer,BUFSIZ);	// 버퍼 초기화
                nBufferLen=0;
                nBufferLen=read(fds[0].fd,szBuffer,BUFSIZ);	// 입력 받은 문자열 읽기
                printf("[%02d] : %s",nBufferLen,szBuffer);
                if(strncasecmp(szBuffer,"EXIT",4)==0) break;
            }
        }

        else if(nRetval==0){
            time(&nCurTime);	// 현재 시간 얻기
            if(nCurTime>=nPrevTime+5){	// 5초마다 현재 시간 출력
                printf("Current : %s",ctime(&nCurTime));
                nPrevTime=nCurTime;	// 이전 시간 갱신
            }
        }
        else{
            perror("Poll exception!!\n");
            return -1;
        }
    }while(1);
    printf("Exiting.\n");
    return 0;
}

