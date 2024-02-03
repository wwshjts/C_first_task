#define BASE_ARR_CAPACITY 10

typedef struct {
    string* data;
    size_t size;
    size_t capacity;
} DynArr;

// typical functions
void arrInit(DynArr* arr);
void arrResize(DynArr* arr);
string* arrPeek(DynArr* arr);
string* arrPop(DynArr* arr);
size_t arrSize(DynArr* arr);
int arrIsEmpty(DynArr* arr);

//unique functions for this data type
void arrAdd(DynArr* arr, string* item);
void arrSet(DynArr* arr, string* s, size_t i);
string* arrGet(DynArr* arr, size_t i);
void arrFree(DynArr* arr);

void arrDelete(DynArr* arr, size_t index);
void arrShrink(DynArr* arr);

void arrPrint(DynArr* arr);
