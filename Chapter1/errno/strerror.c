#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h> // strerror

extern int errno;

int main(){
	char *err;

	if(access("test.txt", R_OK)==-1){
		err = strerror(errno);
		printf("error : %s\n",err);
		exit(1);
	}
}

