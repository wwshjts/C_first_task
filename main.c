#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "strings.h"
#include "support.h"
#include "dynArr.h"
#include "stack.h"

int isPal(String* str);
int isBracket(String* s);
int isMathSign(String* s);
int isExpression(String* s);
int convertToPolish(DynArr* arr, DynArr* res);
int evalPolish(DynArr*, String*);
void evalAllExpr(DynArr* arr); 
void subPals(DynArr* arr); 
void removeBrackets(DynArr* arr); 

int main (int argc, char** argv) {
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
    initEmptyDyn(&arr);

    //skip delimiters
    char ch = getc(fin);
    while( (ch != EOF) && (isDel(ch)) )
        ch = getc(fin);

    //fill array
    arrAddEmpty(&arr);
    strAdd(arrPeek(&arr), ch);    
    while ( ( (ch = getc(fin)) != EOF) ) {
        if (isDel(ch)) {
            arrAddEmpty(&arr);
            strAdd(arrPeek(&arr), ch);
        }
        else if (isWordSymbol(ch) || (ch == '+') || (ch == '-')) {
            //make new word
            if (!strIsWord(arrPeek(&arr))) {
                arrAddEmpty(&arr);
            }
            strAdd(arrPeek(&arr), ch);
        }
        //add punctuation mark
        else {
            arrAddEmpty(&arr);
            strAdd(arrPeek(&arr), ch);
        }
    }        

    //procesing text
    subPals(&arr);
    evalAllExpr(&arr);
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
        String* s = &arr.data[i];
        if (strCmpConst(s, " ") && ((i > 0) && strCmpConst(&arr.data[i - 1], " "))) {
            continue;
        }
        if (strCmpConst(s, "\n") && ( (i > 1) && strCmpConst(&arr.data[i - 1], "\n") && 
                                        strCmpConst(&arr.data[i - 2], "\n"))) {
            continue; 
        }
        fprintString(fout, &arr.data[i]);
        //fprintf(stdout,"%s", arr.data[i].str);
    }
    fprintf(fout, "%c", LF);
    arrFree(&arr);
    if (fclose(fin) != 0) {
        printf("ERROR: trouble in closing file%s\n", argv[1]);
    }
    if (fclose(fout) != 0) {
        printf("ERROR: trouble in closing file%s\n", argv[2]);
    }
    return 0; 
}

//substitute all brackets
void removeBrackets(DynArr* arr) {
    Stack toDelete;
    Stack brackets;
    Stack ind;
    stackInit(&brackets);
    stackInit(&ind);
    stackInit(&toDelete);
    for (size_t i = 0; i < arrSize(arr); i++) {
        String* s = arrGet(arr, i);
        char* word = s->str;
        if ( (strCmpConst(s, "(")) || strIsDel(s)) {
            //if we in this if len(word) > 0
            stackAdd(&brackets, word[0]);
            stackAdd(&ind, i); 
        }
        if (strCmpConst(s, ")") ) {
            int dels = 0;
            while(isDel(stackPeek(&brackets))) {
                dels++;
                stackPop(&brackets);
                stackPop(&ind);
            }
            int first_bracket = stackPop(&ind);
            //if we see the first bracket
            //and we dont have delimiters in ( ... )
            if (i - dels - first_bracket - 1 == 1) {
                stackAdd(&toDelete, first_bracket);
                stackAdd(&toDelete, i);
            }
        }
    }
    stackFree(&brackets);
    stackFree(&ind);
    arrPrint(arr);
    while (stackSize(&toDelete) > 0) {
        arrDelete(arr, stackPop(&toDelete));
    }
    stackFree(&toDelete);
}

//eval all expessions
void evalAllExpr(DynArr* arr) {
    DynArr expr; 
    initEmptyDyn(&expr);
    DynArr res;
    initEmptyDyn(&res);
    String ans;
    strInit(&ans);
    int expr_flag = 0;
    size_t expr_start = 0;
    for (size_t i = 0; i < arrSize(arr); i++) {
        String s = arr->data[i];
        if (isExpression(&s) && (s.str[0] != LF) ) {
            if (!strIsDel(&s)) {
                arrAdd(&expr, &s);
                if (expr_flag == 0) {
                    expr_start = i;
                    expr_flag = 1;
                }
            }
        }
        else {
            int rs = convertToPolish(&expr, &res);
            if (rs > 0) {
                //if expr is converted
                if (evalPolish(&res, &ans)) {
                    strCopy(&arr->data[i-1], &ans);
                    for (size_t dl = expr_start; dl < i-1; dl++) {
                        strWith(&arr->data[dl], " ");                
                    }
                    expr_flag = 0;
                }
            }
            arrFree(&res);
            initEmptyDyn(&res);
            strFree(&ans);
            strInit(&ans);
            arrFree(&expr); 
            initEmptyDyn(&expr);
        }
    }
    arrFree(&expr);
    arrFree(&res);
    strFree(&ans);

}

//substitute all palindroms
void subPals(DynArr* arr){ 
    for (size_t i = 0; i < arrSize(arr); i++) {
        String* str =  arrGet(arr, i); 
        if(isPal(str)) {
            strWith(str,"PALINDROM");
        }
    }
}

int isPal(String* str) {
    char* s = str->str;
    size_t size = strLen(str);
    if (size < 2)
        return 0;

    Stack st;
    stackInit(&st);

    for (size_t i = 0; i < size/2; i++) {
        stackAdd(&st, s[i]);
    }
    
    //case a1a
    printf("size %zu\n", size);
    if ((size % 2 != 0) && (!isLetter(s[size/2]))) {
        printf("hfksdjf");
        return 0;
    }

    for (size_t i = size/2 + (size%2) ; i < size; i++) {
        if (stackPeek(&st) == s[i]) {
            stackPop(&st);
        }
    }
    stackFree(&st);
    return st.size == 0;
}

int isMathSign(String* s) {
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

int isBracket(String* s) {
    if (strCmpConst(s, "("))
        return 1;
    if (strCmpConst(s, ")"))
        return 1;
    return 0;
}

int isExpression(String* s) {
    if (strIsDigit(s))
        return 1;
    if (strIsDel(s))
        return 1;
    if (isBracket(s))
        return 1;
    if (isMathSign(s))
        return 1;
    return 0;
}

int convertToPolish(DynArr* arr, DynArr* res) {
    DynArr st;
    initEmptyDyn(&st);
    for (size_t i = 0; i < arrSize(arr); i++) {
        String curr = arr->data[i];
        if (strIsDigit(&curr)) {
            arrAdd(res, &curr);
        }
        else if (strCmpConst(&curr, ")")) {
            while((st.size > 0) && (!strCmpConst(arrPeek(&st), "(")) ) {
                String* tmp = arrPop(&st);
                arrAdd(res, tmp);
                strFree(tmp);
            }
            if (st.size > 0) {
                strFree(arrPop(&st));
            }
        }
        else{
            arrAdd(&st, &curr);
        }
    }
    if (res -> size == 0)
        return 0;
    while (st.size > 0) {
        if (!isMathSign(arrPeek(&st))) {
            arrFree(&st);
            return 0;
        }
        String* tmp = arrPop(&st);
        arrAdd(res, tmp);
        strFree(tmp);
    }
    arrFree(&st);
    return 1;
}

int evalPolish(DynArr* expr, String* res) {
    Stack st;
    stackInit(&st);
    int errFlag = 0;
    for (size_t i = 0; i < expr->size; i++) {

        String* curr = &expr->data[i];
        if (strIsDigit(curr)) {
            stackAdd(&st, strToInt(curr));
        }
        else {
            if (stackSize(&st) < 2) {
                stackFree(&st);
                return 0;
            }
            char op = expr->data[i].str[0];
            int fr;
            int sc;
            switch(op) {
                case '+' : stackAdd(&st, stackPop(&st) + stackPop(&st));
                break;
                case '-' :
                           sc = stackPop(&st);
                           fr = stackPop(&st);
                           stackAdd(&st, fr - sc);
                break;
                case '*' :
                           stackAdd(&st, stackPop(&st) * stackPop(&st));
                break;
                case '/' : 
                           sc = stackPop(&st);
                           fr = stackPop(&st);
                           if (sc == 0) {
                               errFlag = 1;
                           }
                           else {
                               stackAdd(&st, fr / sc);
                           }
                break;
            }
            if (errFlag) {
                strWith(res, "ERROR");
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
