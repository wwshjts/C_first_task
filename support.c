#include<stdlib.h>
#include<stdio.h>

void nullCheck(void* ptr){
	if(ptr == NULL){
		printf("ERROR: out of memory\n");
		exit(0);
	}
} 
