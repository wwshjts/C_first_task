#include "dynamicArray.h"
DYNAMIC_ARR_GENERATE_HERDER(DynArr, arr, String, *)

//unique functions for this data type
void arrAdd(DynArr* arr, String* item);
void arrSet(DynArr* arr, String* s, size_t i);
String* arrGet(DynArr* arr, size_t i);
void arrFree(DynArr* arr);

void arrDelete(DynArr* arr, size_t index);
void arrShrink(DynArr* arr);

void arrPrint(DynArr* arr);
