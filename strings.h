#define BASE_STRING_CAPACITY 10

typedef struct{
	char* str;
	size_t len;
	size_t capacity;
} string;

void strInit(string* s);
void strAdd(string* s, char ch);
size_t strLen(string* s);

