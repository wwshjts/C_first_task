#include "dynamicArray.h"

DYNAMIC_ARR_GENERATE_HERDER(String, str, char, )
// unique functions for this data sturcture
void strInitWith(String* s, const char* src);
void strSet(String* s, int ch, size_t i);
void strAdd(String* struct_ptr, int ch);
char strGet(String* s, size_t i);
void strCopy(String* struct_dst, String* struct_src);
void strCat(String* struct_dst, String* struct_src);
int strCmp(String* a, String* b);
int strCmpConst(String* arr, const char* b);
int strEndsWith(String* arr, const char* postfix);

void strRestore(String* s);
void strFree(String* s);

int strToInt(String* struct_prt);
void strFloatToString(String* dst, float x);
void strIntToString(String* dst, int x);

int strIsDel(String* s);
int strIsWord(String* s);
int strIsDigit(String* s);

void fprintString(FILE* fl, String* arr);
void strPrint(String* str);
