#include<stddef.h>
#include<stdio.h> 
#include<assert.h>
#include<stdlib.h>
#include<string.h>
#define BASE_STRING_CAPACITY 10
#include"dynamic_arr_generate_header.h"
DYNAMIC_ARR_GENERATE_HEADER(string, char)

//initialize dynamic string with string
//if s.len < strlen(src) then strWith allocates memory
void strWith(string* s, const char* src);
void strAdd(string* struct_ptr, int ch);
size_t strLen(string* struct_ptr);
//find first occurrence of ch in string, return pointer on it
char* strChr(string* struct_prt, int ch);
string* strCopy(string* struct_dst, string* struct_src);
string* strCat(string* struct_dst, string* struct_src);
int strCmp(string* a, string* b);

void strFree(string* s);

int strToInt(string* struct_prt); 
void strFloatToString(string* dst, float x);
void strIntToString(string* dst, int x);

int strIsDel(string* s);
int strIsWord(string* s);
int strIsDigit(string* s);
int strIsLf(string* s);
int strIsSpace(string*s);
