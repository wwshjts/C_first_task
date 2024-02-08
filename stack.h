#include "dynamicArray.h"

DYNAMIC_ARR_GENERATE_HERDER(Stack, stack, int, )

// unique functions for this data structure
void stackSet(Stack* arr, int item, size_t i);
int stackGet(Stack* arr, size_t i);
void stackPrint(Stack* st);
void stackFree(Stack* st);
void stackAdd(Stack* st, int item);
void stackPrint(Stack* st);
