#define _GNU_SOURCE	// Must be written on top
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


int main(){

	char wd[BUFSIZ];	// getcwd()
	char *cwd;	// getcwd(NULL,0) or get_current_dir_name()

	getcwd(wd,BUFSIZ);
	cwd = get_current_dir_name();

	printf("get path with getcwd() : %s\n",wd);
	printf("get_current_dir_name() : %s\n",cwd);
	
	free(cwd);	// dynamic

}

