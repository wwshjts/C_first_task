#pragma once
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "types.h"

typedef struct node {
    struct node* next;
    pointer val;
} header;

typedef struct {
    header* head;
    size_t size;
} headerList;

void initHeaderList(headerList* list);
void addHeader(headerList* list, header* v);
header* storeHeader(pointer mem);
header* getHeader(headerList* list);
int listIsEmpty(headerList* list);