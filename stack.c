#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"
#include "support.h"

//here is typical functions
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

int stackPeek(Stack* st) {
    size_t size = stackSize(st) - 1;
    return st->data[size];
}

int stackPop(Stack* st) {
    assert(stackSize(st) > 0);
    int res = stackPeek(st);
    st->size--;
    return res;
}

size_t stackSize(Stack* st) {
    return st->size;
}

int stackIsEmpty(Stack* st) {
    return stackSize(st) > 0;
}

//here is unique functions for this datastructure
int stackGet(Stack* arr, size_t i) {
    assert(i < stackSize(arr));
    return arr->data[i];
}

void stackSet(Stack* arr, int item, size_t i) {
    assert(i < stackSize(arr));
    arr->data[i] = item;
}

void stackAdd(Stack* st, int item) {
    assert(stackSize(st) < st->capacity);
    st->size++;
    stackSet(st, item, stackSize(st) - 1);
    stackResize(st);
}

void stackFree(Stack* st) {
    free(st->data);
}

void stackPrint(Stack* st) {
    printf("st\n");
    for (size_t i = 0; i < stackSize(st); i++)
        printf("%d ", st->data[i]);
    printf("\n");
}
