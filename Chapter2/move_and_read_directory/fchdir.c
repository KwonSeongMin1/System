#include <fcntl.h>	// fchdir()
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	char *cwd;
	int fd;

	cwd = getcwd(NULL, BUFSIZ);	// Current Directory path
	printf("Current Directory : %s\n",cwd);

	fd = open("test_dir",O_RDONLY);	// File Descripter
	fchdir(fd);

	cwd = getcwd(NULL, BUFSIZ);

	printf("Move directory...\n");

	printf("Success.\nCurrent Directory : %s\n",cwd);
	
	close(fd);
	free(cwd);
}

