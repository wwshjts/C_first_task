#include "dynamicArray.h"
DYNAMIC_ARR_GENERATE_HERDER(DynArr, arr, string, *)

//unique functions for this data type
void arrAdd(DynArr* arr, string* item);
void arrSet(DynArr* arr, string* s, size_t i);
string* arrGet(DynArr* arr, size_t i);
void arrFree(DynArr* arr);

void arrDelete(DynArr* arr, size_t index);
void arrShrink(DynArr* arr);

void arrPrint(DynArr* arr);
