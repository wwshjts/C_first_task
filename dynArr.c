#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"strings.h"
#include"dynArr.h"
#include"support.h"


void initEmptyDyn(DynArr* arr){
	arr->size = 0;
	arr->capacity = BASE_ARR_CAPACITY;
	arr->data = (String*) malloc(sizeof(String) * BASE_ARR_CAPACITY);
	nullCheck(arr->data);
}

void arrResize(DynArr* arr){
	size_t capacity = arr->capacity;

	if(capacity == arr->size){
		capacity = capacity * 2; 
		arr->data = (String*) realloc(arr->data, capacity * sizeof(String));
		nullCheck(arr->data);
	}
	arr->capacity = capacity;
}

void arrAdd(DynArr* arr, String* item){
	String* data = arr->data;

	assert(arr->size <= arr->capacity);

	if(item == NULL){
		strInit(&data[arr->size++]);
	}
	else{
		data[arr->size++] = *item;
	}
	arrResize(arr);
} 

void arrFree(DynArr* arr){
	String* data = arr->data;
	size_t size = arr->size;
	for(size_t i = 0; i < size; i++){
		strFree(&data[i]);
	}
	free(data);
}

String* arrSeek(DynArr* arr){
	size_t size =  (arr->size - 1> 0) ? (arr->size - 1) : 0;
	return &(arr->data[size]);
}

String* arrPop(DynArr* arr){	
	String* res = arrSeek(arr);
	arr->size--;
	return res;
}

void arrShrink(DynArr* arr){
	size_t size = arr->size;
	size_t capacity = arr->capacity;
	if(size <= capacity/4){
		capacity = capacity/4;
		arr->data = (String*) realloc(arr->data, capacity);
		nullCheck(arr->data);
	}
	arr->capacity = capacity;
}
