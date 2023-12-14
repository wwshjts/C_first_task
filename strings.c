#include <stddef.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "strings.h"
#include "support.h"
#include "stack.h"

void strInit(String* struct_ptr) {
    struct_ptr->len = 0;
    struct_ptr->capacity = BASE_String_CAPACITY;
    char* str = (char*) malloc(sizeof(char) * BASE_String_CAPACITY);
    nullCheck(str);
    struct_ptr->str = str;
}

void strResize(String* arr) {
    if (arr->capacity == arr->len) {
        arr->capacity *= 2;
        arr->str = (char *) realloc(arr->str, arr->capacity * sizeof(char));
        nullCheck(arr->str);
    }
}

void strAdd(String* struct_ptr, int ch) {
    char* str = struct_ptr->str;
    assert(struct_ptr->len < struct_ptr->capacity);
    str[struct_ptr->len++] = ch;
    strResize(struct_ptr);
}

char strGet(String* arr, int i) {
    assert(i < arr->len);
    return arr->str[i];
}

size_t strLen(String* struct_ptr) {
    return struct_ptr->len;
}

char* strChr(String* arr, int ch) {
    char* s = arr->str;
    for (size_t i = 0; i < arr->len; i++) {
        if(s[i] == ch){
            //pointer to first accurance of ch
            return s + i;
        }
    }
    return NULL;
}

void strAlloc(String* arr, size_t size){
    size_t capacity = size * 2;
    arr->str = (char*) realloc(arr->str, sizeof(char) * capacity);
    arr->capacity = capacity;
    nullCheck(arr->str);
}

void strCopy(String* dst, String* src) {
    size_t dst_capacity = dst->capacity;
    size_t src_len = src->len;
    if (dst_capacity < src_len) {
        strAlloc(dst, src_len);
    }
    for (size_t i = 0; i < src->len; i++) {
        dst->str[i] = src->str[i];
    }
    dst->len = src->len;
}

void strCat(String* dst, String* src) {
    if(dst->len < src->len){
        strAlloc(dst, dst->len + src->len);
    }
    for(size_t i = dst->len; i < dst->len + src->len; i++){
        dst->str[i] = src->str[i];
    }
    dst->len = dst->len + src->len;
}

int strCmp(String* a, String* b) {
    if(a->len != b->len) return 0;
    for(size_t i = 0; i < a->len; i++){
        if(a->str[i] != b->str[i]) return 0;
    }
    return 1;
}
int strCmpConst(String* arr, const char* b){
    char* a = arr->str;
    size_t a_len = arr->len;
    size_t b_len = strlen(b);
    if (a_len != b_len) return 0;
    for (size_t i = 0; i < a_len; i++) {
        if(a[i] != b[i]) return 0;
    }
    return 1;
}

int strEndsWith(String* arr, const char* postfix){
    size_t postfix_len = strlen(postfix);
    if (arr->len < postfix_len) return 0;
    for (size_t i = arr->len - postfix_len; i < arr->len; i++) {
        if (arr->str[i] != postfix[i - arr->len + postfix_len]) return 0;
    }
    return 1;
}
int strIsDel(String* s) {
    int res = 1;
    for(size_t i = 0; i < strLen(s); i++) {
        res = res && isDel(s->str[i]);
    }
    return res;
}

int strIsWord(String* s) {
    int res = 1;
    for(size_t i = 0; i < s->len; i++) {
        char ch = s->str[i];
        res = res && (isWordSymbol(ch) || (ch == '+') || (ch == '-'));
    }
    return res;
}

int strIsDigit(String* s) {
    int res = 1;
    for (size_t i = 0; i < s->len; i++){
        res = (res && (isDigit(s->str[i])));
    }
    return res;
}

void strFree(String* s) {
    free(s->str);
}

void strWith(String* s, const char* src) {
    char* dst = s->str;
    size_t capacity = s->capacity;
    size_t src_len = strlen(src);
    if (s->len < src_len) {
        free(dst);
        dst = (char*) malloc(sizeof(char) * src_len * 2);
        s->str = dst;
        nullCheck(dst);
        capacity = src_len * 2;
    }
    strcpy(dst, src);
    s->len = src_len;
    s->capacity = capacity;
}

int strToInt(String* s) {
    int res = 0;
    for (size_t i = 0; i < s->len; i++) {
        res += s->str[i] - '0';
        res *= 10;
    }
    res /= 10;
    return res;
}


void strIntToString(String* dst, int x) {
    Stack num;
    stackInit(&num);
    if (x == 0)
        strAdd(dst, '0');
    if (x < 0) {
        strAdd(dst, '-');
        x *= -1;
    }
    while (x > 0) {
        stackAdd(&num, x % 10);
        x /= 10;
    }
    while (num.size > 0) {
        strAdd(dst, stackPop(&num) + '0');
    }
}

void fprintString(FILE* fl, String* arr){
    for(size_t i = 0; i < arr->len; i++){
        putc(arr->str[i], fl);
    }
}

void strFloatToString(String* res, float temp) {
    int x = (int) (temp * 10);
    Stack num;
    stackInit(&num);
    if (x < 0) {
        strAdd(res, '-');
        x *= -1;
    }
    while (x > 0) {
        stackAdd(&num, x % 10);
        x /= 10;
    }
    while (num.size > 1) {
        strAdd(res, stackPop(&num) + '0');
    }
    strAdd(res, '.');
    strAdd(res, stackPop(&num) + '0');
    stackFree(&num);
}

void strPrint(String* str) {
    for (size_t i = 0; i < strLen(str); i++) {
        printf("%c", str->str[i]);
    }
}
