#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "strings.h"
#include "support.h"
#include "dynArr.h"
#include "stack.h"

int isPal(string* str);
int isBracket(string* s);
int isMathSign(string* s);
int isExpression(string* s);
int convertToPolish(DynArr* arr, DynArr* res);
int evalPolish(DynArr*, string*);
void evalExpr(DynArr* arr);
void subPals(DynArr* arr);
int removeBracket(DynArr* arr);
void removeBrackets(DynArr* arr);

int main(int argc, char** argv) {
    FILE* fin;
    FILE* fout;
    if (argc != 3) {
        printf("ERROR: invalid number of arguments\n");
        exit(1);
    }
    if ((fin = fopen(argv[1], "r")) == NULL) {
        printf("ERROR: cant open %s\n", argv[1]);
        exit(1);
    }
    if ((fout = fopen(argv[2], "w")) == NULL) {
        printf("ERROR: cant open %s\n", argv[2]);
        exit(1);
    }
    DynArr arr;
    arrInit(&arr);

    //skip delimiters
    int ch = getc(fin);
    while ( (ch != EOF) && (isDel(ch)) )
        ch = getc(fin);

    //fill array
    char lf = 'x';
    string in_word;
    strInit(&in_word);
    strAdd(&in_word, ch);
    while (((ch = getc(fin)) != EOF)) {
        if (isDel(ch)) {
            arrAdd(&arr,&in_word);
            strRestore(&in_word);
            strAdd(&in_word, ch);
        } else if (isWordSymbol(ch)) {
            if (!strIsWord(&in_word)) {
                arrAdd(&arr, &in_word);
                strRestore(&in_word);
            }
            strAdd(&in_word, ch);
        } else {
            arrAdd(&arr, &in_word);
            strRestore(&in_word);
            strAdd(&in_word, ch);
        }
        lf = ch;
    }
    arrAdd(&arr, &in_word);
    strFree(&in_word);

    //processing text
    subPals(&arr);
    //eval all expr
    evalExpr(&arr);
    //remove all brackets
    removeBrackets(&arr);

    size_t start = 0;
    while ((start < arrSize(&arr)) && strIsDel(arrGet(&arr, start))) {
        start++;
    }

    size_t stop = arrSize(&arr) - 1;
    while ((stop >= 0) && strIsDel(arrGet(&arr, stop))) {
        stop--;
    }

    //delete spaces
    for (size_t i = start; i <= stop; i++) {
        string* s = &arr.data[i];
        if (strCmpConst(s, " ") && ((i > 0) && strIsDel(&arr.data[i - 1]))) {
            continue;
        }
        if (strCmpConst(s, "\n") && ( (i > 1) && strCmpConst(&arr.data[i - 1], "\n") &&
                                        strCmpConst(&arr.data[i - 2], "\n"))) {
            continue;
        }
        fprintString(fout, &arr.data[i]);
    }
    if (lf == LF) {
        fprintf(fout, "%c", LF);
    }

    arrFree(&arr);
    if (fclose(fin) != 0) {
        printf("ERROR: trouble in closing file%s\n", argv[1]);
    }
    if (fclose(fout) != 0) {
        printf("ERROR: trouble in closing file%s\n", argv[2]);
    }
    return 0;
}

void removeBrackets(DynArr* arr) {
    while (removeBracket(arr));
}

//remove first matching pair of brackets
int removeBracket(DynArr* arr) {
    int words = 0;
    int bracket = 0;
    size_t first_bracket = 0;
    for (size_t i = 0; i < arrSize(arr); i++) {
        string* s = arrGet(arr, i);
        if (strCmpConst(s, "(")) {
            first_bracket = i;
            words = 0;
            bracket = 1;
        } else if (strCmpConst(s, ")") && (bracket == 1) && (words == 1)) {
            arrDelete(arr, i);
            arrDelete(arr, first_bracket);
            return 1;
        } else if (strIsWord(s)) {
            words++;
        }
    }
    return 0;
}

//substitute all palindromes
void subPals(DynArr* arr) {
    for (size_t i = 0; i < arrSize(arr); i++) {
        string* str = arrGet(arr, i);
        if (isPal(str)) {
            string tmp;
            strInitWith(&tmp,"PALINDROM");
            arrSet(arr, &tmp, i);
            strFree(&tmp);
        }
    }
}

int isPal(string* str) {
    if (!strIsWord(str)) {
        return 0;
    }
    char* s = str->data;
    size_t size = strSize(str);

    Stack st;
    stackInit(&st);

    for (size_t i = 0; i < size / 2; i++) {
        stackAdd(&st, s[i]);
    }

    //case a1a
    if ((size % 2 != 0) && (!isLetter(s[size / 2]))) {
        stackFree(&st);
        return 0;
    }

    for (size_t i = size / 2 + size % 2; i < size; i++) {
        if (stackPeek(&st) == s[i]) {
            stackPop(&st);
        }
    }
    stackFree(&st);
    return st.size == 0;
}

int isMathSign(string* s) {
    if (strCmpConst(s, "+"))
        return 1;
    if (strCmpConst(s, "-"))
        return 1;
    if (strCmpConst(s, "*"))
        return 1;
    if (strCmpConst(s, "/"))
        return 1;
    return 0;
}

int isBracket(string* s) {
    if (strCmpConst(s, "("))
        return 1;
    if (strCmpConst(s, ")"))
        return 1;
    return 0;
}

int isExpression(string* s) {
    if (strIsDigit(s))
        return 1;
    if (isBracket(s))
        return 1;
    return 0;
}

int convertToPolish(DynArr* arr, DynArr* res) {
    DynArr st;
    arrInit(&st);
    for (size_t i = 0; i < arrSize(arr); i++) {
        string curr = arr->data[i];
        if (strIsDigit(&curr)) {
            arrAdd(res, &curr);
        } else if (strCmpConst(&curr, ")")) {
            while ((st.size > 0) && (!strCmpConst(arrPeek(&st), "("))) {
                string* tmp = arrPop(&st);
                arrAdd(res, tmp);
                strFree(tmp);
            }
            if (st.size > 0) {
                arrDelete(&st, arrSize(&st) - 1);
            }
        } else {
            arrAdd(&st, &curr);
        }
    }
    if (res->size == 0) {
        arrFree(&st);
        return 0;
    }
    while ((st.size > 0) && (isMathSign(arrPeek(&st)))) {
        string* tmp = arrPop(&st);
        arrAdd(res, tmp);
        strFree(tmp);
    }
    arrFree(&st);
    return 1;
}

int evalPolish(DynArr* expr, string* res) {
    Stack st;
    stackInit(&st);
    int errFlag = 0;
    for (size_t i = 0; i < expr->size; i++) {
        string* curr = &expr->data[i];
        if (strIsDigit(curr)) {
            stackAdd(&st, strToInt(curr));
        } else {
            if (stackSize(&st) < 2) {
                stackFree(&st);
                return 0;
            }
            char op = expr->data[i].data[0];
            int sc = stackPop(&st);
            int fr = stackPop(&st);
            switch(op) {
                case '+' :
                    stackAdd(&st, fr + sc); 
                break;
                case '-' :
                    stackAdd(&st, fr - sc); 
                break;
                case '*' :
                    stackAdd(&st, fr * sc); 
                break;
                case '/' :
                    if (sc == 0) {
                        errFlag = 1;
                    } else {
                        stackAdd(&st, fr / sc);
                    }
                break;
            }
            if (errFlag) {
                string tmp;
                strInitWith(&tmp, "ERROR");
                strCopy(res,&tmp);
                strFree(&tmp);
                break;
            }
        }
    }
    if (!errFlag) {
        strIntToString(res, stackPop(&st));
    }
    stackFree(&st);
    return 1;
}

//eval all expressions
void evalExpr(DynArr* arr) {
    DynArr expr;
    arrInit(&expr);
    DynArr res;
    arrInit(&res);
    string ans;
    strInit(&ans);
    Stack toDelete;
    stackInit(&toDelete);
    int expr_flag = 0;
    size_t expr_start = 0;
    size_t expr_end = 0;

    for (size_t i = 0; i < arrSize(arr); i++) {
        string* s = arrGet(arr, i);
        int nothing_happened = 1;
        if (isExpression(s) && expr_flag == 0) {
            arrAdd(&expr, s);
            expr_start = i;
            expr_flag = 1;
            nothing_happened = 0;
        } else if (isExpression(s) || isMathSign(s) || strCmpConst(s, " ")) {
            if (!strIsDel(s)) {
                arrAdd(&expr, s);
                expr_end = i;
            }
            nothing_happened = 0;
        }

        if (nothing_happened || (i == arrSize(arr) - 1)) {
            if (convertToPolish(&expr, &res)) {
                //if expr is converted
                if (evalPolish(&res, &ans)) {
                    arrSet(arr, &ans, expr_start);
                    for (size_t dl = expr_start + 1; dl <= expr_end; dl++) {
                        stackAdd(&toDelete, dl);
                    }
                }
            }
            expr_flag = 0;
            expr_start = 0;
            expr_end = 0;
            arrFree(&res);
            arrInit(&res);
            strFree(&ans);
            strInit(&ans);
            arrFree(&expr);
            arrInit(&expr);
        }
    }
    while (stackSize(&toDelete) > 0) {
        arrDelete(arr, stackPop(&toDelete));
    }
    arrFree(&expr);
    arrFree(&res);
    stackFree(&toDelete);
    strFree(&ans);
}
