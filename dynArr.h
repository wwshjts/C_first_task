#define BASE_ARR_CAPACITY 10

typedef struct {
	String* data;
	size_t size;
	size_t capacity;
} DynArr;

void initEmptyDyn(DynArr* arr);
void arrFree(DynArr* arr);
void arrAdd(DynArr* arr, String* item);
String* arrSeek(DynArr* arr);