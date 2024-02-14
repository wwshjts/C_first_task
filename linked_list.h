#pragma once
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "types.h"

typedef struct node {
    struct node* next;
    struct node* prev;
    pointer val;
} listNode;

typedef struct {
    listNode* head;
    listNode* tail;
    size_t size;
} linkedList;

void listInit(linkedList* list);
void listAddToHead(linkedList* list, listNode* v);
void listAddToTail(linkedList* list,listNode* v);
void listInsertPrev(linkedList* list, listNode* curr, listNode * node);
listNode* listPopHead(linkedList* list);
int listIsEmpty(linkedList* list);
void listFree(linkedList* list);
void listDelete(linkedList*, listNode*);