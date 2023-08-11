#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>


int main(){
	
	struct stat statbuf;
	int kind;

	stat("linux.txt", &statbuf);

	printf("Mode : %o\n", (unsigned int)statbuf.st_mode);

	kind = statbuf.st_mode & S_IFMT;	// S_IFMT : bit mask
	printf("Kind : %o\n", kind);
	
	// search using constant
	switch(kind){
		case S_IFLNK:	// symbolic link
			printf("Symbolic Link\n");
			break;
		case S_IFDIR:	// Directory
			printf("Directory\n");
			break;
		case S_IFREG:	// Regular file
			printf("Regular File\n");
			break;
		}

	// search using macro
	printf("==========================\n");
	if(S_ISLNK(statbuf.st_mode)) printf("Symbolic Link\n");
	if(S_ISDIR(statbuf.st_mode)) printf("Directory\n");
	if(S_ISREG(statbuf.st_mode)) printf("Regular File\n");
}

