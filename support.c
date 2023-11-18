#include <stdlib.h>
#include <stdio.h>
#include "support.h"
void nullCheck(void* ptr) {
    if (ptr == NULL) {
        printf("ERROR: out of memory\n");
        exit(0);
    }
} 

int isDel(char ch) {
    return ch == ' ' || ch == LF;
}

int isWordSymbol(char ch) {
    int isLow = ('a' <= ch) && (ch <= 'z');
    int isBig = ('A' <= ch) && (ch <= 'Z');
    int isDig = ('0' <= ch) && (ch <= '9');
    return isBig || isLow || isDig;
}

int isDigit(char ch) {
    return ('0' <= ch) && (ch <= '9');
}

