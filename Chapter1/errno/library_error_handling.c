#include <stdlib.h>
#include <stdio.h>
#include <errno.h>	//Required to errno variable 

extern int errno;

int main(){
	FILE *fp;

	if((fp=fopen("test.txt", "r"))==NULL){	// Error occurred
		printf("errno=%d\n",errno);
		exit(1);
	}
	fclose(fp);
}

