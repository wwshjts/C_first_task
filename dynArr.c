#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "strings.h"
#include "dynArr.h"
#include "support.h"

//here is typical functions
void arrInit(DynArr* arr) {
    arr->size = 0;
    arr->capacity = BASE_ARR_CAPACITY;
    arr->data = (String*) malloc(sizeof(String) * BASE_ARR_CAPACITY);
    nullCheck(arr->data);
}

void arrResize(DynArr* arr) {
    if (arr->capacity == arr->size) {
        arr->capacity *= 2;
        arr->data = (String*) realloc(arr->data, arr->capacity * sizeof(String));
        nullCheck(arr->data);
    }
}

String* arrPeek(DynArr* arr) {
    assert(arrSize(arr) > 0);
    size_t size = arrSize(arr) - 1;
    return arrGet(arr, size);
}

String* arrPop(DynArr* arr) {
    assert(arrSize(arr) > 0);
    String* res = arrPeek(arr);
    arr->size--;
    return res;
}

size_t arrSize(DynArr* arr) {
    return arr->size;
}

int arrIsEmpty(DynArr* arr) {
    return arr->size > 0;
}

//here is unique functions for this datatype
String* arrGet(DynArr* arr, size_t i) {
    assert(i < arr->size);
    return &arr->data[i];
}

void arrSet(DynArr* arr, String* s, size_t i) {
    assert(i < arrSize(arr));
    strCopy(&arr->data[i], s);
}

void arrAdd(DynArr* arr, String* item) {
    String* data = arr->data;

    assert(arrSize(arr) < arr->capacity);

    //copy content of item(ptr)
    strInit(&data[arr->size]);
    strCopy(&data[arr->size++], item);
    arrResize(arr);
}

void arrFree(DynArr* arr) {
    String* data = arr->data;
    size_t size = arr->size;
    for (size_t i = 0; i < size; i++) {
        strFree(&data[i]);
    }
    free(data);
}

void arrShrink(DynArr* arr) {
    if (arr->size < arr->capacity / 4) {
        arr->capacity /= 4;
        arr->data = (String*) realloc(arr->data, arr->capacity * sizeof(String));
        nullCheck(arr->data);
    }
}

void arrPrint(DynArr* arr) {
    printf("size %zu capacity %zu\n", arr->size, arr->capacity);
    for (size_t i = 0; i < arr->size; i++) {
        printf("<");
        strPrint(&arr->data[i]);
        printf("> ");
    }
    printf("\n");
}

void arrDelete(DynArr* arr, size_t index) {
    assert(index < arr->size);
    for (size_t i = index + 1; i < arrSize(arr); i++) {
        strCopy(&arr->data[i - 1], &arr->data[i]);
    }
    strFree(arrPop(arr));
}
