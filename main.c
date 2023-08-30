#include<stdio.h>
#include<stdlib.h>
#include"strings.h"
#include"support.h"
#include"dynArr.h"
#include"charIs.h"

#define LF 0xa

int main(int argc, char** argv){
	FILE* fin;
	FILE* fout;
	if (argc != 3){
		printf("ERROR: invalid number of arguments\n");
		exit(1);
	}
	if((fin = fopen(argv[1], "r")) == NULL){
		printf("ERROR: cant open %s\n", argv[1]);
		exit(1);
	}
	if((fout = fopen(argv[2], "w")) == NULL){
		printf("ERROR: cant open %s\n", argv[2]);
		exit(1);
	}	

	//allocate dynamic memory for DynArr
	DynArr arr; 
	initEmptyDyn(&arr);
	
	//skip delimiters
	char ch = getc(fin);
	while( (ch != EOF) && (isDel(ch)) )
		ch = getc(fin);

	arrAdd(&arr, NULL);
	strAdd(arrSeek(&arr), ch);	

	//read file to arr, and skip extra delimiters
	while((ch = getc(fin)) != EOF){
		if(ch == ' '){
			if(!strIsDel(arrSeek(&arr))){
				arrAdd(&arr, NULL);
				strAdd(arrSeek(&arr), ch);
			}
		}
		else if((ch == LF) ){
			printf(">%d\n", arr.data[arr.size - 1].str[0]);
			if( (arr.size > 1) && (arr.data[arr.size - 2].str[0] == LF) && \
				(arr.data[arr.size - 1].str[0] == LF) ){
				continue;
			}
			arrAdd(&arr, NULL);
			strAdd(arrSeek(&arr), ch);
		}
		else{
			if (strIsDel(arrSeek(&arr)))
				arrAdd(&arr, NULL);
			strAdd(arrSeek(&arr), ch);
		}
	}

	for(size_t i = 0; i < arr.size; i++){
		fprintf(fout,"%s", arr.data[i].str);
	}
	arrFree(&arr);
	if(fclose(fin) != 0){
		printf("ERROR: trouble in closing file%s\n", argv[1]);
	}
	if(fclose(fout) != 0){
		printf("ERROR: trouble in closing file%s\n", argv[2]);
	}
	return 0; 
}

