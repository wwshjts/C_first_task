#include<stddef.h>
#include<assert.h>
#include<stdlib.h>
#include"strings.h"
#include"support.h"

void strInit(string* struct_ptr){
	struct_ptr->len = 0;
	struct_ptr->capacity = BASE_STRING_CAPACITY;
	char* str = (char*) malloc(sizeof(char) * BASE_STRING_CAPACITY);
	nullCheck(str);
	struct_ptr->str = str;
}

void strAdd(string* struct_ptr, int ch){
	char* str = struct_ptr->str;
	size_t len = struct_ptr->len;
	size_t capacity = struct_ptr->capacity;

	assert(len <= capacity);
	
	str[len++] = ch;
	str[len] = '\0';

	if(capacity - 1 == len){
		capacity = capacity * 2; 
		str = (char *) realloc(str, capacity);
		nullCheck(str);
		struct_ptr->str = str;
	}
	struct_ptr->len = len;
	struct_ptr->capacity = capacity;
}

size_t strLen(string* struct_ptr){
	char* str = struct_ptr->str;
	size_t result = 0;
	while(*str++) result++;
	return result;
}

char* strChr(string* struct_prt, int ch){
	char* s = struct_prt->str; 
	while(*s){
		if(*s == ch)
			return s;
		s++;
	}
	return NULL;
}
