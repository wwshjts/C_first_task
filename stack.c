#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"
#include "support.h"


void stackInit(Stack* st) {
    st->size = 0;
    st->capacity = BASE_STACK_CAPACITY;
    st->data = (int*) malloc(sizeof(int) * BASE_STACK_CAPACITY);
    nullCheck(st->data);
}

void stackResize(Stack* st) {
    if (st->capacity == st->size) {
        st->capacity *= 2; 
        st->data = (int*) realloc(st->data, st->capacity * sizeof(int));
        nullCheck(st->data);
    }
}

void stackAdd(Stack* st, int item) {
    int* data = st->data;

    assert(st->size < st->capacity);

    data[st->size++] = item;
    stackResize(st);
} 

void stackFree(Stack* st) {
    free(st->data);
}

int stackSeek(Stack* st) {
    size_t size = (st->size - 1 > 0) ? (st->size - 1) : 0;
    return st->data[size];
}

int stackIsEmpty(Stack* st) {
    return st->size > 0;
}

int stackPop(Stack* st) {    
    assert(st->size > 0);
    int res = stackSeek(st);
    st->size--;
    stackShrink(st);
    return res;
}

void stackShrink(Stack* st) {
    if (st->size < st->capacity/4) {
        st->capacity /= 4;
        st->data = (int*) realloc(st->data, st->capacity * sizeof(int));
        nullCheck(st->data);
    }
}

void stackPrint(Stack* st) {
    printf("st\n");
    for (size_t i = 0; i < st->size; i++)
        printf("%d ", st->data[i]);
    printf("\n");
}
