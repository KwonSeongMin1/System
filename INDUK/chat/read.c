#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <time.h>
int main(void){

    time_t nTime;	// 현재 시간 저장
    char strBuffer[BUFSIZ];	// 입력한 문자열을 저장하는 버퍼
    int nBufferLen=0;	// 문자열의 길이를 저장

    for(int i=0;;i++){	// 무한 루프

		memset(strBuffer,0,BUFSIZ);	// 버퍼 초기화
        nBufferLen=read(0,strBuffer,BUFSIZ);	// 문자열을 읽어듦임

		if(nBufferLen>0){
            if(strncasecmp(strBuffer,"exit",4)==0) break;	// exit 입력 시 프로그램 종료
            printf("[%02d] : %s", nBufferLen,strBuffer);
        }

        sleep(5);
        time(&nTime);
        printf("Current : %s",ctime(&nTime));	// 현재 시간 출력
    }
     return 0;
}

