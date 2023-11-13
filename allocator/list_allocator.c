#include<stdlib.h>
#include<stdio.h>
#include<stdint.h>
#include"list_allocator.h"
#define DEBUG
typedef uint8_t byte;
//store node to begining of the memory block
void nullcheck(pointer ptr){
    if(!ptr){
        printf("in allocation: Out of memory");
        exit(1);
    }
}
ptrList_node* ptrList_node_init(pointer mem, size_t size){
    ptrList_node* node = (ptrList_node*)mem;
    node->val = mem;
    node->size = size;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

allocator* start_allocate(size_t max_size){
    //allocate memory
    pointer mem = malloc(max_size);
    nullcheck(mem);

    ptrList* list = (ptrList*)(malloc(sizeof(ptrList)));
    nullcheck(list);
    ptrList_init(list);
    
    //first node points to all memory, and store in the same block
    ptrList_node* start = ptrList_node_init(mem, max_size);
    ptrList_add_to_head(list, start);
    
    allocator* a = (allocator*)(malloc(sizeof(allocator)));
    nullcheck(a);

    a->list = list;
    a->mem = mem;
    a->max_size = max_size;
    a->memory_used = 0;
    return a;
}
//returns first fit block, if there is no such block returns null
ptrList_node* find_block(allocator* a, size_t size){
    ptrList_node * curr = a->list->head;
    while(curr){
        if(curr->size >= size)
            break;
        curr = curr->next;
    }
    return curr;
}

void resize_block(allocator* a, ptrList_node* block, size_t size){
    ptrList* list = a->list;
    ptrList_node* new_block = (ptrList_node*)(block->val + size);
    new_block->val = block->val + size;
    new_block->size = block->size - size;
    if(block->prev){
        block->prev->next = new_block;
    }
    else{
        list->head = new_block;
    }
    new_block->prev =  block->prev;
    if(block->next){
        block->next->prev = new_block;
    }
    else{
        list->tail = new_block;
    }
    new_block->next = block->next;
}

pointer list_malloc(allocator* a, size_t size){
    //we need to store header at the begining of the block
    size = size + sizeof(size_t);
    size = (size > sizeof(ptrList_node)) ? size : sizeof(ptrList_node);
    #ifdef DEBUG
    printf("\nactual allocation size: %zu, all memory: %zu, list is %d\n", 
             size, a->max_size - a->memory_used, a->list->size);
    #endif
    if(a->max_size < size){
        return NULL;
    }
    ptrList_node* mem_block = find_block(a, size);
    if(mem_block){
        size_t block_size = mem_block->size;
        pointer block_ptr = mem_block->val;
        a->memory_used += size;
        //if the block is full, then delete it from available blocks
        if(block_size - size < sizeof(ptrList_node)){        
            //alloc all block memory
            a->memory_used = a->memory_used - size + block_size;
            size = block_size;
            ptrList_delete(a->list, mem_block);
        }
        else{
            resize_block(a, mem_block, size);
            #ifdef DEBUG
                ptrList_node* new_block = (ptrList_node*)(block_ptr + size);
                printf("block resized: %p, %zu\n", new_block->val, new_block->size);
            #endif
        }
        //make header for block
        #ifdef DEBUG
            printf("allocation %zu bytes\n", size);
        #endif
        size_t* header = (size_t*)block_ptr;
        *header = size;
        return block_ptr + sizeof(size_t);
    }
    return NULL;
}
//dumb realloc
pointer list_realloc(allocator* a, pointer mem, size_t size){
    size_t block_size = *((size_t* )(mem - sizeof(size_t)));
    pointer new_mem = list_malloc(a, size); 
    if(!new_mem) return NULL;
    for(size_t i = 0; i < size; i++){
        *((byte*)(new_mem + i)) = *((byte*)(mem+i));
    }
    list_free(a, mem);
    return new_mem;
}
void list_free(allocator* a, pointer mem){
    size_t block_size = *((size_t* )(mem - sizeof(size_t)));
    ptrList_node* node = ptrList_node_init(mem - sizeof(size_t), block_size);
    a->memory_used -= block_size;
    //the list is sorted in ascending order of addresses
    ptrList_node* curr = a->list->head;
    while(curr){
        if(curr->val > node->val){
            ptrList_insert_prev(a->list, curr, node);
            break;
        }
        curr = curr->next;
    }
    //if the list is empty or the node address is the largest
    if(!curr){
        ptrList_add_to_tail(a->list, node);
    }
    //merge blocks 
    ptrList_node* prev = node;
    curr = node->next;
    while((curr) && (prev->val + prev->size == curr->val)){
        prev->size += curr->size;
        ptrList_delete(a->list, curr);
        curr = prev->next;
    }
    curr = node->prev;
    while((curr) && (curr->val + curr->size == curr->next->val)){
        curr->size += curr->next->size;
        ptrList_delete(a->list, curr->next);
        curr = curr->prev;
    }
    #ifdef DEBUG
        printf("freed %zu bytes\n", block_size);
        printf("now: mem_used %zu, all mem %zu\n", a->memory_used, a->max_size);
    #endif
}
void stop_allocate(allocator* a){
    free(a->mem);
    free(a);
} 
