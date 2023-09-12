#include <stdio.h>
#include <unistd.h>

int main(void){
	
	int nValue = 0x12345678;
	printf("Value : 0x%08X\n", nValue);

	for(int i=0;i<4;i++){
		
		char *pC = (char *)&nValue+i;
		// Little Endian -> 0x78 0x56 0x34 0x12 (LSB)
		printf("%p : 0x%02X\n", pC, *pC);
	}

	printf("\n");
	return 0;
}

