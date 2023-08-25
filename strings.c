#include<stddef.h>
#include<assert.h>
#include<stdlib.h>
#include"strings.h"
#include"support.h"

void strInit(string* s){
	s->len = 0;
	s->capacity = BASE_STRING_CAPACITY;
	char* str = (char*) malloc(sizeof(char) * BASE_STRING_CAPACITY);
	nullCheck(str);
	s->str = str;
}

void strAdd(string* s, char ch){
	char* str = s->str;
	size_t len = s->len;
	size_t capacity = s->capacity;

	assert(len <= capacity);
	
	str[len++] = ch;
	str[len] = '\0';

	if(capacity - 1 == len){
		capacity = capacity * 2; 
		str = (char *) realloc(str, capacity);
		nullCheck(str);
		s->str = str;
	}
	s->len = len;
	s->capacity = capacity;
}

size_t strLen(string* s){
	char* str = s->str;
	size_t result = 0;
	while(*str++) result++;
	return result;
}
