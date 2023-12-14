#define BASE_String_CAPACITY 10

typedef struct{
    char* str;
    size_t len;
    size_t capacity;
} String;

//initialize an empty string
void strInit(String* struct_ptr);

//initialize dynamic string with string
//if s.len < strlen(src) then strWith allocates memory
void strWith(String* s, const char* src);
void strAdd(String* struct_ptr, int ch);
size_t strLen(String* struct_ptr);
//find first occurrence of ch in string, return pointer on it
char* strChr(String* struct_prt, int ch);
void strCopy(String* struct_dst, String* struct_src);
void strCat(String* struct_dst, String* struct_src);
int strCmp(String* a, String* b);
int strCmpConst(String* arr, const char* b);
int strEndsWith(String* arr, const char* postfix);

void strResise(String* struct_prt);
void strFree(String* s);
void strResize(String* struct_ptr);

int strToInt(String* struct_prt); 
void strFloatToString(String* dst, float x);
void strIntToString(String* dst, int x);

int strIsDel(String* s);
int strIsWord(String* s);
int strIsDigit(String* s);

void fprintString(FILE* fl, String* arr);
void strPrint(String* str); 
