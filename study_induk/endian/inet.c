#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char* argv[]){

	struct in_addr stAddr;
	unsigned char *p = (unsigned char *)&stAddr;
	

	if(argc!=2) return -1;

	printf("IP : %s\n",argv[1]);

	if(inet_aton(argv[1], &stAddr) != 1){
		perror("not converted.");
		return 0;
	}

	printf("Inet Addr : 0x%X\n", st1Addr);

	for(int i=0;i<4;i++){
		printf("[%d] : 0x%02X\n",i,p[i]);
	}

	return 0;
}

