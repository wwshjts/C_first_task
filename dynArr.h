#define BASE_ARR_CAPACITY 10

typedef struct {
    String* data;
    size_t size;
    size_t capacity;
} DynArr;

void arrInit(DynArr* arr);
void arrResize(DynArr* arr);
String* arrPeek(DynArr* arr);
String* arrPop(DynArr* arr);
size_t arrSize(DynArr* arr);
int arrIsEmpty(DynArr* arr);

//unique functions for this data type
void arrAdd(DynArr* arr, String* item);
void arrSet(DynArr* arr, String* s, size_t i);
String* arrGet(DynArr* arr, size_t i);
void arrFree(DynArr* arr);

void arrDelete(DynArr* arr, size_t index);
void arrShrink(DynArr* arr);

void arrPrint(DynArr* arr);
