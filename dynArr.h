#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"dynamicString.h"

#define BASE_ARR_CAPACITY 10
typedef struct {
	string* data;
	size_t size;
	size_t capacity;
} DynArr;

void initEmptyDyn(DynArr* arr);
void arrFree(DynArr* arr);
void arrAdd(DynArr* arr, string* item);

string* arrSeek(DynArr* arr);
string* arrPop(DynArr* arr);
void arrShrink(DynArr* arr);

void arrPrint(DynArr* arr);
