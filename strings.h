#define BASE_STRING_CAPACITY 10

typedef struct{
	char* str;
	size_t len;
	size_t capacity;
} string;

void strInit(string* struct_ptr);
void strAdd(string* struct_ptr, int ch);
size_t strLen(string* struct_ptr);
char* strChr(string* struct_prt, int ch);
string* strCopy(string* struct_dst, string* struct_src);
string* strCat(string* struct_dst, string* struct_src);
int strCmp(string* a, string* b);
void strResise(string* struct_prt);
void strFree(string* s);
