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

String* arrSeek(DynArr* arr) {
    size_t size =  (arr->size - 1> 0) ? (arr->size - 1) : 0;
    return &(arr->data[size]);
}

String* arrPop(DynArr* arr) {    
    String* res = arrSeek(arr);
    arr->size--;
    arrShrink(arr);
    return res;
}

void arrShrink(DynArr* arr) {
    size_t size = arr->size;
    size_t capacity = arr->capacity;
    if (size < capacity/4) {
        capacity = capacity/4;
        arr->data = (String*) realloc(arr->data, capacity * sizeof(String));
        nullCheck(arr->data);
    }
    arr->capacity = capacity;
}

void arrPrint(DynArr* arr) {
    printf("size %zu capacity %zu\n", arr->size, arr->capacity);
    for (size_t i = 0; i < arr->size; i++)
        printf("<%s> ", arr->data[i].str);
    printf("\n");
}
