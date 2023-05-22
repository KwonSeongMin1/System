#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(void){
	
	int nPid=0;
	nPid=fork();
	if(nPid==0){
		printf("I am a child.(PID : %d)\n",nPid);
	}
	else{
		printf("I am a parent.(PID : %d)\n",nPid);
	}
	return 0;
}

