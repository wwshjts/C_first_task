#include<stdio.h>
#include<stdlib.h>
#include"strings.h"
#include"support.h"

int main(void){
	string s;
	strInit(&s);
	char ch;
	while((ch = getchar()) != '\n')
		strAdd(&s, ch);
	printf("%s\n", s.str);
	return 0; 
}
