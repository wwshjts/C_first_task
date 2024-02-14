#include "linked_list.h"

void listInit(linkedList* list) {
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

void listAddToHead(linkedList* list, listNode* v) {
    if (list->head) {
        v->next = list->head;
        list->head->prev = v;
        list->head = v;
    } else {
        list->head = v;
        list->tail = v;
    }
    list->size++;
}

void listAddToTail(linkedList* list, listNode* v) {
    if (list->tail) {
        list->tail->next = v;
        v->prev = list->tail;
        list->tail = v;
    } else {
        list->head = v;
        list->tail = v;
    }
    list->size++;
}

void listFree(linkedList* list) {
    while (list->head) {
        listNode* curr = list->head;
        list->head = curr->next;
        free(curr);
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

int listIsEmpty(linkedList * list) {
    return (list->head == NULL) && (list->tail == NULL);
}

listNode* listPopHead(linkedList * list) {
    listNode * curr = list->head;
    list->size--;
    list->head = curr->next;
    if (!list->head) {
        list->tail = NULL;
    } else {
        list->head->prev = NULL;
    }
    return curr;
}

void listInsertPrev(linkedList * list, listNode* curr, listNode* node) {
    if (!curr->prev) { 
        listAddToHead(list, node);
    } else {
        list->size++;
        node->next = curr;
        node->prev = curr->prev;
        curr->prev->next = node;
        curr->prev = node;
    }
}

void listDelete(linkedList* list, listNode* node){
    listNode* prev = node->prev;
    listNode* next = node->next;
    list->size--;

    if (!prev && !next) {
        list->head = NULL;
        list->tail = NULL;
    }

    if (prev && next) {
        next->prev = prev;
        prev->next = next;
    }

    if (prev && !next) {
        prev->next = NULL;
        list->tail = prev;
    }

    if (!prev && next) {
        next->prev = NULL;
        list->head = next;
    }
}