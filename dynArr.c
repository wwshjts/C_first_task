#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "strings.h"
#include "dynArr.h"
#include "support.h"

void initEmptyDyn(DynArr* arr) {
    arr->size = 0;
    arr->capacity = BASE_ARR_CAPACITY;
    arr->data = (String*) malloc(sizeof(String) * BASE_ARR_CAPACITY);
    nullCheck(arr->data);
}

size_t arrSize(DynArr* arr) {
    return arr->size;
}

void arrResize(DynArr* arr) {
    if (arr->capacity == arr->size) {
        arr->capacity *= 2;
        arr->data = (String*) realloc(arr->data, arr->capacity * sizeof(String));
        nullCheck(arr->data);
    }
}

void arrAdd(DynArr* arr, String* item) {
    String* data = arr->data;

    assert(arr->size < arr->capacity);

    //copy content of item(ptr)
    strInit(&data[arr->size]);
    strCopy(&data[arr->size++], item);
    arrResize(arr);
}

String* arrGet(DynArr* arr, int i) {
    assert(i < arr->size);
    return &arr->data[i];
}

void arrAddEmpty(DynArr* arr){
    String* data = arr->data;

    assert(arr->size < arr->capacity);

    strInit(&data[arr->size++]);
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

int arrIsEmpty(DynArr* arr){
    return arr->size > 0;
}

String* arrPeek(DynArr* arr) {
    assert(arr->size > 0);
    size_t size = (arr->size - 1 > 0) ? (arr->size - 1) : 0;
    return &arr->data[size];
}

String* arrPop(DynArr* arr) {
    assert(arr->size > 0);
    String* res = arrPeek(arr);
    arr->size--;
    arrShrink(arr);
    return res;
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
    for (size_t i = index + 1; i < arrSize(arr); i++){
        *arrGet(arr, i - 1) = *arrGet(arr, i);
    }
    arr->size--;
}
