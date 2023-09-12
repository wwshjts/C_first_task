#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"strings.h"
#include"support.h"
#include"dynArr.h"
#include"charIs.h"
#include"stack.h"
#define LF 0xa

int isPal(String* str);
int isTemperature(String* s);
int isBracket(String* s);
int isMathSign(String* s);
int isExpression(String* s);
void convertTemp(String* s);


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
		else if((ch == LF)){
			if( !((arr.size > 1) && (arr.data[arr.size - 2].str[0] == LF) && \
				(arr.data[arr.size - 1].str[0] == LF) )){
				arrAdd(&arr, NULL);
				strAdd(arrSeek(&arr), ch);
			}
		}
		else if(isAlpha(ch) || (ch == '+') || (ch == '-')){
			if (!strIsWord(arrSeek(&arr))){
				arrAdd(&arr, NULL);
			}
			strAdd(arrSeek(&arr), ch);
		}		
		else{
			arrAdd(&arr, NULL);
			strAdd(arrSeek(&arr), ch);
		}
	}

	//procesing text
	int ruleFlag = 1;
	while(ruleFlag){
		ruleFlag = 0;
		Stack brackets;
		Stack ind;
		DynArr expr;
		stackInit(&brackets);
		stackInit(&ind);
		initEmptyDyn(&expr);
		for(size_t i = 0; i < arr.size; i++){
			String s = arr.data[i];
			char* word = s.str;
			if(isPal(&arr.data[i])){
				strWith(&arr.data[i], "PALINDROM");
				ruleFlag = 1;
			}
			if( (word[0] == '(') || strIsDel(&s)){
				stackAdd(&brackets, word[0]);
				stackAdd(&ind, i); 
			}
			if(word[0] == ')'){
				int dels = 0;
				while(isDel(stackSeek(&brackets))){
					dels++;
					stackPop(&brackets);
					stackPop(&ind);
				}
				int tmp = stackPop(&ind);
				if(i - dels - tmp - 1 == 1){
					strInit(&arr.data[i]);
					strWith(&arr.data[i]," ");
					strInit(&arr.data[tmp]);
					strWith(&arr.data[tmp]," ");
					ruleFlag = 1;
				}
			}
			if(isTemperature(&s)){
				convertTemp(&s);
			}	
		}
		stackFree(&brackets);
		stackFree(&ind);
	}

	for(size_t i = 0; i < arr.size; i++){
		/*if(!strIsDel(&arr.data[i]))
			printf("<%s>\n", arr.data[i].str); */
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
	if(size < 2)
		return 0;
	Stack st;
	stackInit(&st);
	for(size_t i = 0; i < size/2; i++){
		stackAdd(&st, s[i]);
	}

	for(size_t i = size/2 + (size%2) ; i < size; i++){
		if(stackSeek(&st) == s[i]){
			stackPop(&st);
		}
	}
	return st.size == 0;
}

int isTemperature(String* s){
	char* str = s->str;
	if( (str[0] != '+') && (str[0] != '-' ))
		return 0;
	str++;	
	int digitFlag = 0;
	while(isDigit(*str)){	
		digitFlag = 1;
		str++;
	}
	int suffix = (strcmp(str, "tF") == 0);
	return suffix && digitFlag;
}

void convertTemp(String* s){
	char* str = s->str; 
	char sign = *str++;
	String res;
	strInit(&res);
	float temp = 0;
	while(*str != 't'){
	 	temp += *str - '0';
		temp *= 10;
		str++;
	}
	temp /= 10;
	if(sign == '-')
		temp *= -1;
	temp = (temp - 32) * (5.0 / 9);
	int x = (int) (temp * 10);
	Stack num;
	stackInit(&num);
	if(x < 0){
		strAdd(&res, '-');
		x *= -1;
	}
	printf("%d\n", x);
	while (x > 0){
		stackAdd(&num, x % 10);
		x /= 10; 
	}
	while (num.size > 1){
		strAdd(&res, stackPop(&num) + '0');
	}
	strAdd(&res, '.');
	strAdd(&res, stackPop(&num) + '0');
	strAdd(&res, 't');
	strAdd(&res, 'C');
	strCopy(s, &res);
}
int isMathSign(String* s){
	char* word = s->str;
	if (strcmp(word, "+") == 0)
		return 1;
	if (strcmp(word, "-") == 0)
		return 1;
	if (strcmp(word, "*") == 0)
		return 1;
	if (strcmp(word, "/") == 0)
		return 1;
	return 0;
}

int isBracket(String* s){
	char* word = s->str;
	if (strcmp(word, "(") == 0)
		return 1;
	if (strcmp(word, ")") == 0)
		return 1;
	return 0;
}

int isExpression(String* s){
	if (strIsDigit(s))
		return 1;
	if (strIsDel(s))
		return 1;
	if (isBracket(s))
		return 1;
	if (isMathSign(s))
		return 1;
	return 0;
}

