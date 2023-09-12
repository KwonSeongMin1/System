#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>

#define MAX_FD 4

int main(void){

	int fd[MAX_FD] = {-1,};
	
	printf("Process ID : %d\n", getpid());

	for(int i=0;i<MAX_FD;i++){
		fd[i] = socket(PF_INET, SOCK_STREAM, 0);
	}

	getchar();

	for(int i=0;i<MAX_FD;i++){
		close(fd[i]);
	}

	getchar();

	return 0;
}

