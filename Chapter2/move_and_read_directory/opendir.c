#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>	// readdir()

int main(){

	DIR *dp;
	struct dirent *dent;	// to return readdir(), sys/dirent.h check

	dp = opendir(".");	// Read current directory

	while((dent = readdir(dp))){

		printf("Name : %s ", dent -> d_name);
		printf("Inode : %d\n", (int)dent -> d_ino);
	}

	closedir(dp);
}

