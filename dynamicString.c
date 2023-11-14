#include"dynamicString.h"
#include"stack.h"
#include"dynamic_arr_generate_code.h"

DYNAMIC_ARR_GENERATE_CODE(string, char)

void strAdd(string* struct_ptr, int ch){
	char* str = struct_ptr->data;
	assert(struct_ptr->size <= struct_ptr->capacity);
	str[struct_ptr->size++] = ch;
	str[struct_ptr->size] = '\0';
	string_resize(struct_ptr);
}

size_t strLen(string* struct_ptr){
	return struct_ptr->size;
}

char* strChr(string* struct_prt, int ch){
	char* s = struct_prt->data; 
	while(*s){
		if(*s == ch)
			return s;
		s++;
	}
	return NULL;
}

string* strCopy(string* dst, string* src){	
	size_t dst_capacity = dst->capacity;
	size_t src_len = src->size;
	if(dst_capacity < src_len){
		free(dst->data);
		dst_capacity = src_len * 2;
		dst->data = (char*) malloc(sizeof(char) * dst_capacity);
		nullCheck(dst->data);
	}
	strcpy(dst->data, src->data);
	dst->size = src->size;
	dst->capacity = dst_capacity;
	return dst;
}

//assume that dst.len <= dst.src
string* strCat(string* struct_dst, string* struct_src){
	string* result = struct_dst;
	struct_dst->data = strcat(struct_dst->data, struct_src->data);
	struct_dst->size = struct_src->size + struct_dst->size;
	return result;
}

int strCmp(string* a, string* b){
	return strcmp(a->data, b->data);
}

int strIsDel(string* s){
	int res = 1;
	for(size_t i = 0; i < s->size; i++){
		res = res && isDel(s->data[i]);
	}
	return res;
}

int strIsWord(string* s){
	int res = 1;
	for(size_t i = 0; i < s->size; i++){
		char ch = s->data[i];
		res = res && (isAlpha(ch) || (ch == '+') || (ch == '-'));
	}
	return res;
}

int strIsDigit(string* s){
	char* word = s->data;
	int res = 1;
	while(*word){
		res = (res && (isDigit(*word)));
		word++;
	}
	return res;
}

int strIsSpace(string*s){
	char* word = s->data;
	int res = 0;
	while(*word){
		res = (*word == ' ');
		word++;
	}
	return res; 
}

int strIsLf(string* s){
	char* word = s->data;
	int res = 0;
	while(*word){
		res = (*word == LF);
		word++;
	}
	return res;
}
void strFree(string* s){
	free(s->data);
}

void strWith(string* s, const char* src){
	char* dst = s->data;
	size_t capacity = s->capacity;
	size_t src_len = strlen(src);
	if(s->size < src_len){
		free(dst);
		dst = (char*) malloc(sizeof(char) * src_len * 2);
		nullCheck(dst);
		capacity = src_len * 2;
	}
	strcpy(dst, src);
	s->size = src_len;
	s->capacity = capacity;
	s->data = dst;
}

int strToInt(string* s){
	char* word = s->data;
	int res = 0;	
	while(isDigit(*word)){	
		res += *word - '0';
		res *= 10;
		word++;
	}
	res /= 10;
	return res;
}


void strIntToString(string* dst, int x){
	Stack num;
	stackInit(&num);
	if (x == 0)
		strAdd(dst, '0');
	if(x < 0){
		strAdd(dst, '-');
		x *= -1;
	}
	while (x > 0){
		stackAdd(&num, x % 10);
		x /= 10; 
	}
	while (num.size > 0){
		strAdd(dst, stackPop(&num) + '0');
	}
}


void strFloatToString(string* res, float temp){
	int x = (int) (temp * 10);
	Stack num;
	stackInit(&num);
	if(x < 0){
		strAdd(res, '-');
		x *= -1;
	}
	while (x > 0){
		stackAdd(&num, x % 10);
		x /= 10; 
	}
	while (num.size > 1){
		strAdd(res, stackPop(&num) + '0');
	}
	strAdd(res, '.');
	strAdd(res, stackPop(&num) + '0');
	stackFree(&num);
}
