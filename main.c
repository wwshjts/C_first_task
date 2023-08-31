#include<stdio.h>
#include<stdlib.h>
#include"strings.h"
#include"support.h"
#include"dynArr.h"
#include"charIs.h"
#include"stack.h"

#define LF 0xa

int isPal(String* str);

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
	
	String tmp;
	strInit(&tmp);
	strWith(&tmp, "why");
	printf("%d\n", strIsWord(&tmp));
	//read file to arr, and skip extra delimiters
	while((ch = getc(fin)) != EOF){
		if(ch == ' '){
			if(!strIsDel(arrSeek(&arr))){
				arrAdd(&arr, NULL);
				strAdd(arrSeek(&arr), ch);
			}
		}
		else if((ch == LF)){
			if( !((arr.size > 1) && (arr.data[arr.size - 2].str[0] == LF) && \
				(arr.data[arr.size - 1].str[0] == LF) )){
				arrAdd(&arr, NULL);
				strAdd(arrSeek(&arr), ch);
			}
		}
		else if(isAlpha(ch) || (ch == '+') || (ch == '-')){
			if (!strIsWord(arrSeek(&arr))){
				printf(">%c\n", ch);
				arrAdd(&arr, NULL);
			}
			strAdd(arrSeek(&arr), ch);
		}		
		else{
			arrAdd(&arr, NULL);
			strAdd(arrSeek(&arr), ch);
		}
	}

	for(size_t i = 0; i < arr.size; i++){
		printf("<%s>\n", arr.data[i].str);
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

int isPal(String* str){
	char* s = str->str;
	size_t size = str->len;
	Stack st;
	stackInit(&st);
	for(size_t i = 0; i < size/2; i++){
		printf(">%c\n", s[i]);
		stackAdd(&st, s[i]);
	}

	for(size_t i = size/2 + (size%2) ; i < size; i++){
		if(stackSeek(&st) == s[i]){
			stackPop(&st);
		}
	}
	return st.size == 0;
}


