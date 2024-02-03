#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "strings.h"
#include "dynArr.h"
#include "support.h"

DYNAMIC_ARR_GENERATE_CODE(DynArr, arr, string, *)

//here is unique functions for this datatype
string* arrGet(DynArr* arr, size_t i) {
    assert(i < arr->size);
    return &arr->data[i];
}

void arrSet(DynArr* arr, string* s, size_t i) {
    assert(i < arrSize(arr));
    strCopy(&arr->data[i], s);
}

void arrAdd(DynArr* arr, string* item) {
    string* data = arr->data;

    assert(arrSize(arr) < arr->capacity);

    //copy content of item(ptr)
    strInit(&data[arr->size]);
    strCopy(&data[arr->size++], item);
    arrResize(arr);
}

void arrFree(DynArr* arr) {
    string* data = arr->data;
    size_t size = arr->size;
    for (size_t i = 0; i < size; i++) {
        strFree(&data[i]);
    }
    free(data);
}

void arrShrink(DynArr* arr) {
    if (arr->size < arr->capacity / 4) {
        arr->capacity /= 4;
        arr->data = (string*) realloc(arr->data, arr->capacity * sizeof(string));
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
