#include <stdio.h>
#include <unistd.h>
#include <errno.h>	// Required to errno variable

extern int errno;

int main(){
	if(access("test.txt", F_OK)==-1){	// Error occurred
		printf("errno=%d\n", errno);
	}
}

