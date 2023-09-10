#include <sys/utsname.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
	struct utsname uts;


	// uname
	if(uname(&uts)==-1){
		perror("uname");
		exit(1);
	}

	printf("OS name : %s\n", uts.sysname);
	printf("Node name : %s\n", uts.nodename);
	printf("Release : %s\n", uts.release);
	printf("Version : %s\n", uts.version);
	printf("Machine : %s\n", uts.machine);
}
