// Stored Heap memory
#include <stdio.h>
#include <stdlib.h>

int main(){
	char *ptr1;
	char *ptr2;

	ptr1 = malloc(sizeof(char) * 10);
	ptr2 = calloc(1,10);
	for(int i=0;i<10;i++){
		ptr1[i] = i+65;
		printf("ptr1[%d] = %c\n",i,ptr1[i]);
	}

	printf("======================================\n");

	for(int i=0;i<10;i++){
		ptr2[i] = i+65;
		printf("ptr1[%d] = %c\n",i,ptr1[i]);
	}


	free(ptr1);
	free(ptr2);
}


