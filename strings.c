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

char strGet(String* arr, int i) {
    assert(i < arr->len);
    return arr->str[i];
}

void strSet(String* arr, int ch, size_t i) {
    assert(i <= strLen(arr));
    arr->str[i] = ch;
}

void strAdd(String* arr, int ch) {
    assert(strLen(arr) < arr->capacity);
    strSet(arr, ch, strLen(arr));
    arr->len++;
    strResize(arr);
}

size_t strLen(String* struct_ptr) {
    return struct_ptr->len;
}

void strAlloc(String* arr, size_t size) {
    size_t capacity = size * 2;
    arr->str = (char*) realloc(arr->str, sizeof(char) * capacity);
    arr->capacity = capacity;
    nullCheck(arr->str);
}

void strCopy(String* dst, String* src) {
    size_t dst_capacity = dst->capacity;
    size_t src_len = strLen(src);

    if (dst_capacity < src_len) {
        strAlloc(dst, src_len);
    }

    for (size_t i = 0; i < src_len; i++) {
        dst->str[i] = strGet(src, i);
    }
    dst->len = src->len;
}

void strCat(String* dst, String* src) {
    if (strLen(dst) < strLen(dst)) {
        strAlloc(dst, strLen(dst) + strLen(src));
    }
    for (size_t i = dst->len; i < dst->len + src->len; i++) {
        dst->str[i] = src->str[i];
    }
    dst->len = dst->len + src->len;
}

int strCmp(String* a, String* b) {
    if (strLen(a) != strLen(b)) return 0;
    for (size_t i = 0; i < strLen(a); i++) {
        if (strGet(a, i) != strGet(b, i)) return 0;
    }
    return 1;
}

int strCmpConst(String* arr, const char* b) {
    char* a = arr->str;
    size_t a_len = strLen(arr);
    size_t b_len = strlen(b);
    if (a_len != b_len) return 0;
    for (size_t i = 0; i < a_len; i++) {
        if (a[i] != b[i]) return 0;
    }
    return 1;
}

int strEndsWith(String* arr, const char* postfix) {
    size_t postfix_len = strlen(postfix);
    if (strLen(arr) < postfix_len) return 0;
    for (size_t i = strLen(arr) - postfix_len; i < arr->len; i++) {
        if (strGet(arr, i) != postfix[i - strLen(arr) + postfix_len]) return 0;
    }
    return 1;
}

int strIsDel(String* s) {
    int res = 1;
    for (size_t i = 0; i < strLen(s); i++) {
        res = res && isDel(strGet(s, i));
    }
    return res;
}

int strIsWord(String* s) {
    assert(strLen(s) > 0);
    int res = isWordSymbol(strGet(s, 0)) || (strGet(s, 0) == '+') || (strGet(s ,0) == '-') ;
    for (size_t i = 1; i < strLen(s); i++) {
        res = res && (isWordSymbol(strGet(s,  i)));
    }
    return res;
}

int strIsDigit(String* s) {
    if (strLen(s) > 9) {
        return 0;
    }

    int res = 1;
    for (size_t i = 0; i < s->len; i++) {
        res = (res && (isDigit(strGet(s, i))));
    }
    return res;
}

void strFree(String* s) {
    free(s->str);
}

void strInitWith(String* s, const char* src) {
    strInit(s);

    while(*src) {
        strAdd(s, *src);
        src++;
    }
}

int strToInt(String* s) {
    long res = 0;
    for (size_t i = 0; i < s->len; i++) {
        res += strGet(s, i) - '0';
        res *= 10;
    }
    res /= 10;
    return res;
}

void strIntToString(String* dst, int x) {
    Stack num;
    stackInit(&num);
    if (x == 0) {
        strAdd(dst, '0');
    }
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

void fprintString(FILE* fl, String* arr) {
    for (size_t i = 0; i < arr->len; i++) {
        putc(strGet(arr, i), fl);
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
