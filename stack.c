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

size_t stackSize(Stack* st) {
    return st->size;
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

    assert(stackSize(st) < st->capacity);

    data[st->size++] = item;
    stackResize(st);
}

void stackFree(Stack* st) {
    free(st->data);
}

int stackPeek(Stack* st) {
    size_t size = stackSize(st) - 1;
    return st->data[size];
}

int stackIsEmpty(Stack* st) {
    return stackSize(st) > 0;
}

int stackPop(Stack* st) {
    assert(stackSize(st) > 0);
    int res = stackPeek(st);
    st->size--;
    stackShrink(st);
    return res;
}

void stackShrink(Stack* st) {
    if (stackSize(st) < st->capacity / 4) {
        st->capacity /= 4;
        st->data = (int*) realloc(st->data, st->capacity * sizeof(int));
        nullCheck(st->data);
    }
}

void stackPrint(Stack* st) {
    printf("st\n");
    for (size_t i = 0; i < stackSize(st); i++)
        printf("%d ", st->data[i]);
    printf("\n");
}
