#include "dynamicArray.h"

DYNAMIC_ARR_GENERATE_HERDER(string, str, char, )
// unique functions for this data sturcture
void strInitWith(string* s, const char* src);
void strSet(string* s, int ch, size_t i);
void strAdd(string* struct_ptr, int ch);
char strGet(string* s, size_t i);
void strCopy(string* struct_dst, string* struct_src);
void strCat(string* struct_dst, string* struct_src);
int strCmp(string* a, string* b);
int strCmpConst(string* arr, const char* b);
int strEndsWith(string* arr, const char* postfix);

void strRestore(string* s);
void strFree(string* s);

int strToInt(string* struct_prt);
void strFloatToString(string* dst, float x);
void strIntToString(string* dst, int x);

int strIsDel(string* s);
int strIsWord(string* s);
int strIsDigit(string* s);

void fprintString(FILE* fl, string* arr);
void strPrint(string* str);
