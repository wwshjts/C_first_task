#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"
#include "support.h"
#include "dynamicArray.h"

DYNAMIC_ARR_GENERATE_CODE(Stack, stack, int, )

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
