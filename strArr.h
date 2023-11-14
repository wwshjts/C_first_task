#include"dynamicString.h"
#include"dynamic_arr_generate_header.h"

DYNAMIC_ARR_GENERATE_HEADER(strArr, string)

void strArr_add(strArr* arr, string* item);
void strArr_free(strArr* arr);
void strArr_print(strArr* arr);
