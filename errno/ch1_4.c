// perror() function 

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int main(){

	char *err;

	if(access("test.txt", R_OK) == -1){
		err = strerror(errno);
		printf("perror message >>> ");
		perror("test.txt");
		printf("\nstrerror message >>> error : %s(test.txt)\n", err);
		exit(1);
	}
}

