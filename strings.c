#include<stddef.h>
#include<stdio.h> 
#include<assert.h>
#include<stdlib.h>
#include<string.h>
#include"strings.h"
#include"support.h"
#include"stack.h"

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
    return struct_ptr->len;
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

String* strCopy(String* dst, String* src){    
    size_t dst_capacity = dst->capacity;
    size_t src_len = src->len;
    if(dst_capacity < src_len){
        free(dst->str);
        dst_capacity = src_len * 2;
        dst->str = (char*) malloc(sizeof(char) * dst_capacity);
        nullCheck(dst->str);
    }
    strcpy(dst->str, src->str);
    dst->len = src->len;
    dst->capacity = dst_capacity;
    return dst;
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
        res = res && (isAlpha(ch) || (ch == '+') || (ch == '-'));
    }
    return res;
}

int strIsDigit(String* s){
    char* word = s->str;
    int res = 1;
    while(*word){
        res = (res && (isDigit(*word)));
        word++;
    }
    return res;
}

int strIsSpace(String*s){
    char* word = s->str;
    int res = 0;
    while(*word){
        res = (*word == ' ');
        word++;
    }
    return res; 
}

int strIsLf(String* s){
    char* word = s->str;
    int res = 0;
    while(*word){
        res = (*word == LF);
        word++;
    }
    return res;
}
void strFree(String* s){
    free(s->str);
}

void strWith(String* s, const char* src){
    char* dst = s->str;
    size_t capacity = s->capacity;
    size_t src_len = strlen(src);
    if(s->len < src_len){
        free(dst);
        dst = (char*) malloc(sizeof(char) * src_len * 2);
        nullCheck(dst);
        capacity = src_len * 2;
    }
    strcpy(dst, src);
    s->len = src_len;
    s->capacity = capacity;
    s->str = dst;
}

int strToInt(String* s){
    char* word = s->str;
    int res = 0;    
    while(isDigit(*word)){    
        res += *word - '0';
        res *= 10;
        word++;
    }
    res /= 10;
    return res;
}


void strIntToString(String* dst, int x){
    Stack num;
    stackInit(&num);
    if (x == 0)
        strAdd(dst, '0');
    if(x < 0){
        strAdd(dst, '-');
        x *= -1;
    }
    while (x > 0){
        stackAdd(&num, x % 10);
        x /= 10; 
    }
    while (num.size > 0){
        strAdd(dst, stackPop(&num) + '0');
    }
}


void strFloatToString(String* res, float temp){
    int x = (int) (temp * 10);
    Stack num;
    stackInit(&num);
    if(x < 0){
        strAdd(res, '-');
        x *= -1;
    }
    while (x > 0){
        stackAdd(&num, x % 10);
        x /= 10; 
    }
    while (num.size > 1){
        strAdd(res, stackPop(&num) + '0');
    }
    strAdd(res, '.');
    strAdd(res, stackPop(&num) + '0');
    stackFree(&num);
}
