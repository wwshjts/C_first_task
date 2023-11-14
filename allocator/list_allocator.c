#include<stdlib.h>
#include<stdio.h>
#include<stdint.h>
#include"list_allocator.h"
#define DEBUG

typedef uint8_t byte;

void memcheck(pointer ptr){
    if(!ptr){
        printf("in allocation: Out of memory");
        exit(1);
    }
}

//store node to begining of the memory block
ptrList_node* ptrList_node_init(pointer mem, size_t size){
    ptrList_node* node = (ptrList_node*)mem;
    node->val = mem;
    node->size = size;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

allocator* start_allocate(size_t chunk_size, size_t n){
    if(chunk_size < sizeof(ptrList_node)){
        return NULL;
    }
    //allocate memory
    pointer mem = malloc(chunk_size * n);
    memcheck(mem);

    ptrList* list = (ptrList*)(malloc(sizeof(ptrList)));
    memcheck(list);
    ptrList_init(list);
    
    allocator* a = (allocator*)(malloc(sizeof(allocator)));
    memcheck(a);

    a->list = list;
    a->mem = mem;
    a->n = n;
    a->chunk_size = chunk_size;
    a->memory_used = 0;
    for(size_t i = 0; i < n; i++){
        ptrList_add_to_head(list, ptrList_node_init(mem + i * chunk_size, chunk_size));
    }
    return a;
}

pointer list_malloc(allocator* a){ 
    if(ptrList_is_empty(a->list)) return NULL;
    pointer res = a->list->head->val;
    ptrList_delete(a->list, a->list->head);
    return res;
}

//dumb realloc
pointer list_realloc(allocator* a, pointer mem){
   return mem; 
}
void list_free(allocator* a, pointer mem){
    ptrList_node* node = ptrList_node_init(mem, a->chunk_size);
    ptrList_add_to_head(a->list, node);
}

void stop_allocate(allocator* a){
    free(a->mem);
    free(a);
} 
