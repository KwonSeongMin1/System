#include <sys/stat.h>	// mkdir()
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>	// rmdir()

int main(){

	// mkdir
	if(mkdir("Hello!!!",0755)==-1){
		perror("Hello!!!");
		exit(1);
	}
	
	// rmdir
	if(rmdir("Hello!!!")==-1){
		perror("Hello!!!");
		exit(1);
	}

}

