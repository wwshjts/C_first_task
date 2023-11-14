#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"strArr.h"
#include"support.h"
#include"stack.h"

int isPal(String* str);
int isTemperature(String* s);
int isBracket(String* s);
int isMathSign(String* s);
int isExpression(String* s);
void convertTemp(String* s);
int convertToPolish(strArr*, strArr*);
int evalPolish(strArr*, String*);


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

	strArr arr; 
	strArr_init(&arr);

	//skip delimiters
	char ch = getc(fin);
	while( (ch != EOF) && (isDel(ch)) )
		ch = getc(fin);

    //fill array
	strArr_add(&arr, NULL);
	strAdd(strArr_seek(&arr), ch);	
	while ( ( (ch = getc(fin)) != EOF) ){
		if (isDel(ch)){
			strArr_add(&arr, NULL);
			strAdd(strArr_seek(&arr), ch);
		}
		else if(isAlpha(ch) || (ch == '+') || (ch == '-')){
            //make new word
			if (!strIsWord(strArr_seek(&arr))){
				strArr_add(&arr, NULL);
			}
			strAdd(strArr_seek(&arr), ch);
		}
        //add punctuation mark
		else{
			strArr_add(&arr, NULL);
			strAdd(strArr_seek(&arr), ch);
		}
	}		

	//eval all expressions in the file
	strArr expr; 
	strArr_init(&expr);
	strArr res;
	strArr_init(&res);
	String ans;
	strInit(&ans);
	int expr_flag = 0;
	size_t expr_start = 0;
	for(size_t i = 0; i < arr.size; i++){
		String s = arr.data[i];
		if(isExpression(&s) && (s.str[0] != LF) ){
			if(!strIsDel(&s)){
				strArr_add(&expr, &s);
				if (expr_flag == 0){
					expr_start = i;
					expr_flag = 1;
				}
			}
		}
		else {
			int rs = convertToPolish(&expr, &res);
			if (rs > 0){
				//if expr is converted
				if (evalPolish(&res, &ans)){
					strCopy(&arr.data[i-1], &ans);
					for(size_t dl = expr_start; dl < i-1; dl++){
						strWith(&arr.data[dl], " ");				
					}
					expr_flag = 0;
				}
			}
			strArr_free(&res);
			strArr_init(&res);
			strFree(&ans);
			strInit(&ans);
			strArr_free(&expr); 
			strArr_init(&expr);
		}

	}
    strArr_free(&expr);
    strArr_free(&res);
    strFree(&ans);
	//procesing text
	int ruleFlag = 1;
	while(ruleFlag){
		ruleFlag = 0;
		Stack brackets;
		Stack ind;
		stackInit(&brackets);
		stackInit(&ind);
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
    
    size_t start = 0;
    while(strIsDel(&arr.data[start])){
        start++;
    }
    //delete spaces
	for(size_t i = start; i < arr.size; i++){
		String s = arr.data[i];
		if (strIsSpace(&s) && ((i > 0) && strIsSpace(&arr.data[i - 1])))
			continue;
		if (strIsLf(&s) && ( (i > 1) && strIsLf(&arr.data[i - 1]) && \
										strIsLf(&arr.data[i - 2])))
			continue; 
		fprintf(fout,"%s", arr.data[i].str);
	}
	strArr_free(&arr);
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
    stackFree(&st);
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
	strFloatToString(&res, temp);
	strAdd(&res, 't');
	strAdd(&res, 'C');
	strCopy(s, &res);
    strFree(&res);
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

int convertToPolish(strArr* arr, strArr* res){
	strArr st;
	strArr_init(&st);
	for(size_t i = 0; i < arr->size; i++){
		String curr = arr->data[i];
		if(strIsDigit(&curr)){
			strArr_add(res, &curr);
		}
		else if(strcmp(curr.str, ")") == 0){
			while((st.size > 0) && (strcmp(strArr_seek(&st)->str, "(") != 0) ){
				strArr_add(res, strArr_pop(&st));
			}
			if(st.size > 0){
				strArr_pop(&st);
			}
		}
		else{
			strArr_add(&st, &curr);
		}
	}
	if(res -> size == 0)
		return 0;
	while(st.size > 0){
		if(!isMathSign(strArr_seek(&st))){
            strArr_free(&st);
			return 0;
        }
		strArr_add(res, strArr_pop(&st));
	}
    strArr_free(&st);
	return 1;
}

int evalPolish(strArr* expr, String* res){
	Stack st;
	stackInit(&st);
	int errFlag = 0;
	for(size_t i = 0; i < expr->size; i++){

		String* curr = &expr->data[i];
		if (strIsDigit(curr)){
			stackAdd(&st, strToInt(curr));
		}
		else{
			char op = expr->data[i].str[0];
			int fr;
			int sc;
			switch(op){
				case '+' : stackAdd(&st, stackPop(&st) + stackPop(&st));
				break;
				case '-' :
						   sc = stackPop(&st);
						   fr = stackPop(&st);
						   stackAdd(&st, fr - sc);
				break;
				case '*' :
						   stackAdd(&st, stackPop(&st) * stackPop(&st));
				break;
				case '/' : 
						   sc = stackPop(&st);
						   fr = stackPop(&st);
						   if (sc == 0){
							   errFlag = 1;
						   }
                           else {
                               stackAdd(&st, fr / sc);
                           }
				break;
			}
			if (errFlag){
				strWith(res, "ERROR");
                break;
		    }
		}
	}
    if(!errFlag){
	    strIntToString(res, stackPop(&st));
    }
	stackFree(&st);

	return 1;
}
