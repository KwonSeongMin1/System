#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]){

	in_addr_t stAddr;
	unsigned char *p = (unsigned char*)&stAddr;

	if(argc!=2) return -1;
	
	printf("IP Address : %s\n", argv[1]);

	// IP -> Big-Endian
	stAddr = inet_addr(argv[1]);

	printf("Inet Addr : 0x%X\n", stAddr);
	for(int i=0;i<4;i++){
		printf("[%d] = 0x%02X\n",i,p[i]);
	}

	return 0;
}


