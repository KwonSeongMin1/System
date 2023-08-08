#include <stdlib.h>	// dynamic memory
#include <stdio.h>

int main(){

	int *malloc_ptr;
	int *calloc_ptr;

	malloc_ptr = (int*)malloc(sizeof(int)*10);	// Memory needs to be initialized
	calloc_ptr = (int*)calloc(10,sizeof(int));	// Initialized to 0

	for(int i=0;i<10;i++){
		malloc_ptr[i] = i;
		printf("malloc_ptr[%d] = %d\n",i,malloc_ptr[i]);
	}
	
	printf("=======================================\n");

	for(int i=0;i<10;i++){
		calloc_ptr[i] = i;
		printf("calloc_ptr[%d] = %d\n",i,calloc_ptr[i]);
	}

	free(malloc_ptr);
	free(calloc_ptr);
}


