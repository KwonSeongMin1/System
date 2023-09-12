#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(void){

	int value = 0x12345678;
	uint32_t htonsValue = htons(value);
	uint32_t htonlValue = htonl(value);

	// Little Endian
	printf("value = 0x%08X\n", value);
	for(int i=0;i<4;i++){
		char *p = (char*)&value+i;
		printf("%p : 0x%02X\n",p,*p);
	}

	// Big Endian (just 2 Bytes)
	printf("htons = 0x%08X\n", htonsValue);
	for(int i=0;i<4;i++){
		char *p = (char*)&htonsValue+i;
		printf("%p : 0x%02X\n",p,*p);
	}
	
	// Big Endian (4 Bytes)
	printf("htonl = 0x%08X\n", htonlValue);
	for(int i=0;i<4;i++){
		char *p = (char*)&htonlValue+i;
		printf("%p : 0x%02X\n",p,*p);
	}
	
	return 0;
}

