#include <stdio.h> // perror
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

int main(){
	if(access("test.txt", R_OK)==-1) { //if system call error occurred -> -1 return
		perror("test.txt");
		exit(1);
	}
}
