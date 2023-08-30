#include<stddef.h>
#include<stdio.h> 
#include<assert.h>
#include<stdlib.h>
#include<string.h>
#include"strings.h"
#include"support.h"
#include"charIs.h"

void strInit(String* struct_ptr){
	struct_ptr->len = 0;
	struct_ptr->capacity = BASE_String_CAPACITY;
	char* str = (char*) malloc(sizeof(char) * BASE_String_CAPACITY);
	nullCheck(str);
	struct_ptr->str = str;
}

void strResize(String* struct_ptr){
	char* str = struct_ptr->str;
	size_t len = struct_ptr->len;
	size_t capacity = struct_ptr->capacity;

	if(capacity - 1 == len){
		capacity = capacity * 2; 
		str = (char *) realloc(str, capacity * sizeof(char));
		nullCheck(str);
		struct_ptr->str = str;
	}
	struct_ptr->len = len;
	struct_ptr->capacity = capacity;

}

void strAdd(String* struct_ptr, int ch){
	char* str = struct_ptr->str;
	assert(struct_ptr->len <= struct_ptr->capacity);
	
	str[struct_ptr->len++] = ch;
	str[struct_ptr->len] = '\0';

	strResize(struct_ptr);
}

size_t strLen(String* struct_ptr){
	char* str = struct_ptr->str;
	size_t result = 0;
	while(*str++) result++;
	return result;
}

char* strChr(String* struct_prt, int ch){
	char* s = struct_prt->str; 
	while(*s){
		if(*s == ch)
			return s;
		s++;
	}
	return NULL;
}

//assume that dst.len <= dst.src
String* strCopy(String* struct_dst, String* struct_src){	
	String* result = struct_dst;
	struct_dst->str = strcpy(struct_dst->str, struct_src->str);
	struct_dst->len = struct_src->len;
	return result;
}

//assume that dst.len <= dst.src
String* strCat(String* struct_dst, String* struct_src){
	String* result = struct_dst;
	struct_dst->str = strcat(struct_dst->str, struct_src->str);
	struct_dst->len = struct_src->len + struct_dst->len;
	return result;
}

int strCmp(String* a, String* b){
	return strcmp(a->str, b->str);
}

int strIsDel(String* s){
	int res = 1;
	for(size_t i = 0; i < s->len; i++){
		res = res && isDel(s->str[i]);
	}
	return res;
}

int strIsWord(String* s){
	int res = 1;
	for(size_t i = 0; i < s->len; i++){
		char ch = s->str[i];
		res = res && (isAlpha(ch) || (ch == 0x2b) || (ch == 0x2d));
	}
	return res;
}

void strFree(String* s){
	free(s->str);
}

void strWith(String* s, const char* src){
	char* dst = s->str;
	size_t capacity = s->capacity;
	int src_len = strlen(src);
	if(s->len < src_len){
		free(dst);
		dst = (char*) malloc(sizeof(char) * strlen(src) + 2);
		nullCheck(dst);
		capacity = src_len + 2;
	}
	strcpy(dst, src);
	s->len = src_len + 1;
	s->capacity = capacity;
	s->str = dst;
}
