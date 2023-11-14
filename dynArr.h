#ifndef CUSTOM_ALLOC
#include"allocator/list_allocator.h"
#endif

#define BASE_ARR_CAPACITY 10

typedef struct {
	String* data;
	size_t size;
	size_t capacity;
    allocator* alloc; 
} DynArr;

void initEmptyDyn(allocator* a, DynArr* arr);
void arrFree(DynArr* arr);
void arrAdd(DynArr* arr, String* item);

String* arrSeek(DynArr* arr);
String* arrPop(DynArr* arr);
void arrShrink(DynArr* arr);

void arrPrint(DynArr* arr);
