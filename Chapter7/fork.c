#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


void print_test_code(){
	printf("Test atexit code...\n");
}



int main(){
	pid_t pid;

	switch(pid=fork()){
		case -1:
			perror("fork");
			exit(1);
			break;
		case 0:
			printf("Child - PID : %d / Parent's PID : %d\n",(int)getpid(), (int)getppid());
			atexit(print_test_code);
			break;
		default:
			printf("Parent - PID : %d / Parent's PID : %d / Child PID : %d\n",(int)getpid(), (int)getppid(), (int)pid);
			break;
	}

	printf("End.\n");
}
