#include"support.h"
#define DYNAMIC_ARR_GENERATE_CODE(NAME, T)\
void NAME##_init(NAME * arr){\
	arr->size = 0;\
	arr->capacity = BASE_ARR_CAPACITY;\
	arr->data = (T *) malloc(sizeof(T) * BASE_ARR_CAPACITY);\
	nullCheck(arr->data);\
}\
void NAME##_resize(NAME * arr){\
	size_t capacity = arr->capacity;\
	if(capacity == arr->size){\
		capacity = capacity * 2; \
		arr->data = (T *) realloc(arr->data, capacity * sizeof(T));\
		nullCheck(arr->data);\
	}\
	arr->capacity = capacity;\
}\
T * NAME##_seek(NAME * arr){\
	size_t size =  (arr->size - 1> 0) ? (arr->size - 1) : 0;\
	return &(arr->data[size]);\
}\
T * NAME##_pop(NAME * arr){	\
	T * res = NAME##_seek(arr);\
	arr->size--;\
	NAME##_shrink(arr);\
	return res;\
}\
void NAME##_shrink(NAME * arr){\
	size_t size = arr->size;\
	size_t capacity = arr->capacity;\
	if(size < capacity/4){\
		capacity = capacity/4;\
		arr->data = (T *) realloc(arr->data, capacity * sizeof(T));\
		nullCheck(arr->data);\
	}\
	arr->capacity = capacity;\
}
