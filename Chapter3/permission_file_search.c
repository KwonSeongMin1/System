#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int main(){
	
	struct stat statbuf;
	stat("linux.txt", &statbuf);
	printf("Mode : %o\n",(unsigned int)statbuf.st_mode);

	if((statbuf.st_mode & S_IREAD) != 0) printf("User has a read permission\n");
	if((statbuf.st_mode & (S_IREAD >> 3)) != 0) printf("Group has a read permission\n");	// or S_IRGRP
	if((statbuf.st_mode & S_IROTH) != 0) printf("Other have a read permission\n");	// or S_IREAD >> 6
}

