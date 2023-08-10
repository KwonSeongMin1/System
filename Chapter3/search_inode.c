#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

int main(){
	
	int fd;
	struct stat statbuf1;	// inode information that use stat()
	struct stat statbuf2;	// fstat()

	stat("linux.txt", &statbuf1);	// use stat()

	fd = open("linux.txt", O_RDONLY);
	if(fd==-1){
		perror("open: linux.txt");
		exit(1);
	}

	fstat(fd, &statbuf2);	// use fstat()


	printf("======== stat() ========\n");
	printf("Inode = %d\n", (int)statbuf1.st_ino);
	printf("Mode = %o\n", (unsigned int)statbuf1.st_mode);
	printf("Nlink = %o\n",(unsigned int)statbuf1.st_nlink);
	printf("UID = %d\n\n",(int)statbuf1.st_uid);

	printf("======= fstat() ========\n");
   	printf("Inode = %d\n", (int)statbuf2.st_ino);
    printf("Mode = %o\n", (unsigned int)statbuf2.st_mode);
    printf("Nlink = %o\n",(unsigned int)statbuf2.st_nlink);
    printf("UID = %d\n\n",(int)statbuf2.st_uid);

	close(fd);
}

