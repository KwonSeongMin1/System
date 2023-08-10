#include <unistd.h> // chdir()
#include <stdio.h>
#include <stdlib.h>

int main(){
	char *cwd;

	cwd = getcwd(NULL, BUFSIZ);	// Current Directory path
	printf("Current Directory : %s\n",cwd);

	chdir("test_dir");	// Move directory in program

	printf("Move Directory...\n");

	cwd = getcwd(NULL, BUFSIZ);
	printf("Success.\nCurrent Directory : %s\n",cwd);
	
	free(cwd);
}

