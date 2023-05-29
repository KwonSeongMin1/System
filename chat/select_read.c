#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

int main(void){

    fd_set rfds;	// 파일 디스크립터 집합
    struct timeval tv;	// select 함수에 사용되는 대기시간 설정
    int nRet;	// select 함수 return값
    time_t nTime;	// 현재 시간 저장변수
    char szBuffer[BUFSIZ];	// 입력된 문자열 저장 버퍼
    int nBufferLen=0;	// 문자열 길이 저장 변수

    do{	// 무한루프
        FD_ZERO(&rfds);	// 파일 디스크립터 집합 초기화
        FD_SET(0, &rfds);	// 표준 입력 파일 디스크립터를 집합에 추가
        tv.tv_sec=5;	// 대기시간 5초
        tv.tv_usec=0;

        nRet=select(1,&rfds,NULL,NULL,&tv);	// select 함수, 입력 대기

        if(nRet>0){
            if(FD_ISSET(0,&rfds)){	// 표준 입력 파일 디스크립터가 준비되었는지 확인
                memset(szBuffer,0,BUFSIZ);	// 버퍼 초기화
                nBufferLen=read(0,szBuffer,BUFSIZ);	// 문자열 읽기
                if(nBufferLen>0){
                    if(strncasecmp(szBuffer,"exit",4)==0) break;	// exit 입력시 프로그램 종료
                    printf("[%02d] : %s",nBufferLen,szBuffer);
                }
            }
        }
        else{	// 대기시간 초과 시
            time(&nTime);
            printf("Current : %s",ctime(&nTime));	// 현재시간 출력
        }
    } while(1);
    return 0;
}

