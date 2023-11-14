#include"strArr.h"
#include"dynamic_arr_generate_code.h"

DYNAMIC_ARR_GENERATE_CODE( strArr, string )

void strArr_add(strArr* arr, string* item){
	string* data = arr->data;

	assert(arr->size <= arr->capacity);

	//if the argument is NULL then add an empty string
	if(item == NULL){
		string_init(&data[arr->size++]);
	}
	else{
		//copy content of item(ptr)
		string_init(&data[arr->size]);
		strCopy(&data[arr->size++], item);
	}
	strArr_resize(arr);
}

void strArr_free(strArr* arr){
	string* data = arr->data;
	size_t size = arr->size;
	for(size_t i = 0; i < size; i++){
		strFree(&data[i]);
	}
	free(data);
}

void strArr_print(strArr* arr){
	printf("size %zu capacity %zu\n", arr->size, arr->capacity);
	for(size_t i = 0; i < arr->size; i++)
		printf("<%s> ", arr->data[i].data);
	printf("\n");
}
