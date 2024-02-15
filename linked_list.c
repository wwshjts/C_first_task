#include <assert.h>
#include "linked_list.h"

void initHeaderList(headerList *list) {
    list->head = NULL;
    list->size = 0;
}

header* storeHeader(pointer mem) {
    header* h = (header*) mem;
    h->next = NULL;
    h->val = mem;
    return h;
}

void addHeader(headerList* list, header* h) {
    h->next = list->head;
    list->head = h;
    list->size++;
}

header* getHeader(headerList* list) {
    assert(!listIsEmpty(list));

    header* h = list->head;

    list->head = h->next;
    list->size--;
    return h;
}

int listIsEmpty(headerList* list) {
    return (list->head == NULL);
}
