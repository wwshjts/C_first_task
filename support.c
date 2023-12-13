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

int isLetter(char ch) {
    int isLow = ('a' <= ch) && (ch <= 'z');
    int isBig = ('A' <= ch) && (ch <= 'Z');
    return isBig || isLow;
}

int isWordSymbol(char ch) {
    return isLetter(ch) || isDigit(ch);
}

int isDigit(char ch) {
    return ('0' <= ch) && (ch <= '9');
}

