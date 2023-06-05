#include <stdio.h>
#include <unistd.h>
#include <poll.h>

#define TIMEOUT 5

int main(){
	struct pollfd fds[2];
	int ret;
	
	// 표준 입력 이벤트 감시
	fds[0].fd = STDIN_FILENO;
	fds[0].events = POLLIN;	// 읽을 데이터가 존재(not block)

	// 표준 출력 이벤트 감시
	fds[1].fd = STDOUT_FILENO;
	fds[1].events = POLLOUT;	// 쓰기 not block

	ret = poll(fds, 2, TIMEOUT * 1000);
	
	if(ret == -1){
		perror("poll");
		return -1;
	}

	if(!ret){
		printf("%d seconds elapsed.\n",TIMEOUT);
		return 0;
	}
	
	if(fds[0].revents & POLLIN) printf("stdin is readable\n");
	if(fds[1].revents & POLLOUT) printf("stdout is writeable\n");
	return 0;
}


