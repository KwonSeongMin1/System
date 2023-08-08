#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
	if(rename("testdir","ttestddir")==-1){
		perror("rename");
		exit(1);
	}
}

