#pragma once

#define BASE_ARR_CAPACITY 10

#define DYNAMIC_ARR_GENERATE_HERDER(NAME, PREFIX, T, REFERENCE_TYPE)\
typedef struct{\
    T * data;\
    size_t size;\
    size_t capacity;\
} NAME;\
void PREFIX##Init(NAME *);\
void PREFIX##Resize(NAME *);\
T REFERENCE_TYPE PREFIX##Peek(NAME *);\
T REFERENCE_TYPE PREFIX##Pop(NAME *);\
size_t PREFIX##Size(NAME *);\
int PREFIX##IsEmpty(NAME *);

#define DYNAMIC_ARR_GENERATE_CODE(NAME, PREFIX, T, REFERENCE_TYPE)\
void PREFIX##Init(NAME * arr) {\
    arr->size = 0;\
    arr->capacity = BASE_ARR_CAPACITY;\
    arr->data = (T *) malloc(sizeof(T) * BASE_ARR_CAPACITY);\
    nullCheck(arr->data);\
}\
\
void PREFIX##Resize(NAME * arr) {\
    if (arr->capacity == arr->size) {\
        arr->capacity *= 2;\
        arr->data = (T *) realloc(arr->data, arr->capacity * sizeof(T));\
        nullCheck(arr->data);\
    }\
}\
\
T REFERENCE_TYPE PREFIX##Peek(NAME * arr) {\
    assert(PREFIX##Size(arr) > 0);\
    size_t size = PREFIX##Size(arr) - 1;\
    return PREFIX##Get(arr, size);\
}\
\
T REFERENCE_TYPE PREFIX##Pop(NAME * arr) {\
    assert(PREFIX##Size(arr) > 0);\
    T * res = PREFIX##Peek(arr);\
    arr->size--;\
    return res;\
}\
\
size_t PREFIX##Size(NAME * arr) {\
    return arr->size;\
}\
\
int PREFIX##IsEmpty(NAME* arr) {\
    return PREFIX##Size(arr) == 0;\
}