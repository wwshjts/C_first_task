#include <stddef.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "strings.h"
#include "support.h"
#include "stack.h"
#include "dynamicArray.h"

DYNAMIC_ARR_GENERATE_CODE(string, str, char, )

//here is unique functions for this datastructure
char strGet(string* arr, size_t i) {
    assert(i < strSize(arr));
    return arr->data[i];
}

void strSet(string* arr, int ch, size_t i) {
    assert(i < strSize(arr));
    arr->data[i] = ch;
}

void strAdd(string* arr, int ch) {
    assert(strSize(arr) < arr->capacity);
    arr->size++;
    strSet(arr, ch, strSize(arr) - 1);
    strResize(arr);
}

void strFree(string* s) {
    free(s->data);
}

void strAlloc(string* arr, size_t size) {
    size_t capacity = size * 2;
    arr->data = (char*) realloc(arr->data, sizeof(char) * capacity);
    arr->capacity = capacity;
    nullCheck(arr->data);
}

void strCopy(string* dst, string* src) {

    size_t dst_capacity = dst->capacity;
    size_t src_len = strSize(src);

    if (dst_capacity < src_len) {
        strAlloc(dst, src_len);
    }

    for (size_t i = 0; i < src_len; i++) {
        dst->data[i] = strGet(src, i);
    }
    dst->size = src_len;
}

void strCat(string* dst, string* src) {
    if (strSize(dst) < strSize(dst)) {
        strAlloc(dst, strSize(dst) + strSize(src));
    }
    for (size_t i = dst->size; i < strSize(dst) + strSize(src); i++) {
        strSet(dst, strGet(src, i), i);
    }
    dst->size = strSize(dst) + strSize(src);
}

int strCmp(string* a, string* b) {
    if (strSize(a) != strSize(b)) return 0;
    for (size_t i = 0; i < strSize(a); i++) {
        if (strGet(a, i) != strGet(b, i)) return 0;
    }
    return 1;
}

int strCmpConst(string* arr, const char* b) {
    char* a = arr->data;
    size_t a_len = strSize(arr);
    size_t b_len = strlen(b);
    if (a_len != b_len) return 0;
    for (size_t i = 0; i < a_len; i++) {
        if (a[i] != b[i]) return 0;
    }
    return 1;
}

int strEndsWith(string* arr, const char* postfix) {
    size_t postfix_len = strlen(postfix);
    if (strSize(arr) < postfix_len) return 0;
    for (size_t i = strSize(arr) - postfix_len; i < arr->size; i++) {
        if (strGet(arr, i) != postfix[i - strSize(arr) + postfix_len]) return 0;
    }
    return 1;
}

int strIsDel(string* s) {
    int res = 1;
    for (size_t i = 0; i < strSize(s); i++) {
        res = res && isDel(strGet(s, i));
    }
    return res;
}

int strIsWord(string* s) {
    if (strSize(s) == 0) return 1;
    int res = isWordSymbol(strGet(s, 0)) || (strGet(s, 0) == '+') || (strGet(s, 0) == '-');
    for (size_t i = 1; i < strSize(s); i++) {
        res = res && (isWordSymbol(strGet(s, i)));
    }
    return res;
}

int strIsDigit(string* s) {
    if (strSize(s) > 9) {
        return 0;
    }

    int res = 1;
    for (size_t i = 0; i < s->size; i++) {
        res = (res && (isDigit(strGet(s, i))));
    }
    return res;
}

void strRestore(string* s) {
    strFree(s);
    strInit(s);
}

void strInitWith(string* s, const char* src) {
    strInit(s);
    while (*src) {
        strAdd(s, *src);
        src++;
    }
}

int strToInt(string* s) {
    long res = 0;
    for (size_t i = 0; i < s->size; i++) {
        res += strGet(s, i) - '0';
        res *= 10;
    }
    res /= 10;
    return res;
}

void strIntToString(string* dst, int x) {
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
    stackFree(&num);
}

void fprintString(FILE* fl, string* arr) {
    for (size_t i = 0; i < strSize(arr); i++) {
        putc(strGet(arr, i), fl);
    }
}

void strFloatToString(string* res, float temp) {
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

void strPrint(string* str) {
    for (size_t i = 0; i < strSize(str); i++) {
        printf("%c", str->data[i]);
    }
}
