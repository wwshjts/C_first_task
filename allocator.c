#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "allocator.h"
#include "linked_list.h"

#define DEBUG

typedef struct{
    linkedList* list;
    pointer mem;
    size_t n;
    size_t memory_used;
    size_t chunk_size;
} allocator;

static allocator* a;

static void memcheck(pointer ptr){
    if(!ptr){
        printf("in allocation: Out of memory");
        exit(1);
    }
}

//store node to begining of the memory block
listNode* storeNodeAtList(pointer mem){
    listNode* node = (listNode*)mem;
    node->val = mem;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

void startAllocate(size_t chunk_size, size_t n) {
    //in this case we can't build our allocator
    assert(chunk_size > sizeof(listNode));
    
    //allocate memory
    pointer mem = malloc(chunk_size * n);
    memcheck(mem);

    linkedList* list = (linkedList*)(malloc(sizeof(linkedList)));
    memcheck(list);
    listInit(list);
    
    a = (allocator*)(malloc(sizeof(allocator)));
    memcheck(a);

    a->list = list;
    a->mem = mem;
    a->n = n;
    a->chunk_size = chunk_size;
    a->memory_used = 0;

    for(size_t i = 0; i < n; i++){
        listAddToHead(list, storeNodeAtList(mem + i * chunk_size));
    }
}

pointer myAlloc(){ 
    if(listIsEmpty(a->list)) return NULL;
    listNode* header = listPopHead(a->list);
    a->memory_used++;
    #ifdef DEBUG
        printf("memory allocated: chuncks used %zu; all chuncks %zu\n", a->memory_used, a->n);
    #endif
    return header->val;
}

//dumb realloc and it's okey
pointer myRealloc(pointer mem){
   return mem; 
}

void myAllocatorFree(pointer mem){
    listNode* node = storeNodeAtList(mem);
    a->memory_used--;
    listAddToHead(a->list, node);
}

void myAllocatorStopAllocate(){
    free(a->mem);
    free(a);
}