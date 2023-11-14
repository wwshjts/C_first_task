#define BASE_ARR_CAPACITY 10
#define DYNAMIC_ARR_GENERATE_HEADER(NAME, T)\
typedef struct {\
	T * data;\
	size_t size;\
	size_t capacity;\
} NAME;\
void NAME##_init(NAME* arr);\
String* NAME##_seek(NAME* arr);\
String* NAME##_pop(NAME* arr);\
void NAME##_shrink(NAME* arr);\
void NAME##_resize(NAME* arr);
