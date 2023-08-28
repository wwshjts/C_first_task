#define BASE_String_CAPACITY 10

typedef struct{
	char* str;
	size_t len;
	size_t capacity;
} String;

void strInit(String* struct_ptr);
void strWith(String* s, const char* src);
void strAdd(String* struct_ptr, int ch);
size_t strLen(String* struct_ptr);
char* strChr(String* struct_prt, int ch);
String* strCopy(String* struct_dst, String* struct_src);
String* strCat(String* struct_dst, String* struct_src);
int strCmp(String* a, String* b);
void strResise(String* struct_prt);
void strFree(String* s);
void strResize(String* struct_ptr);

int strIsDel(String* s);
int strIsWord(String* s);
