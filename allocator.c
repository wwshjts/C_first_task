#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "allocator.h"
#include "linked_list.h"

//#define DEBUG

#ifdef DEBUG
    pointer* allocated_mem;
#endif

typedef struct{
    headerList* list;
    pointer mem;
    pointer mem_end;
    size_t n;
    size_t chunks_used;
    size_t chunk_size;
} allocator;

static allocator* a;

static void memcheck(pointer ptr){
    if (ptr == NULL) {
        printf("in allocation: Out of memory");
        exit(1);
    }
}

void startAllocate(size_t chunk_size, size_t n) {
    pointer mem = calloc(n, chunk_size);
    memcheck(mem);

    headerList* list = (headerList*) malloc(sizeof(headerList));
    memcheck(list);
    initHeaderList(list);

    #ifdef DEBUG
        allocated_mem = (pointer*) malloc(sizeof(pointer) * n);
        memcheck(allocated_mem);
        for (size_t i = 0; i < n; i++) {
            allocated_mem[i] = mem + chunk_size * i;
        }
    #endif

    for (size_t i = 0; i < n; i++) {
        addHeader(list, storeHeader(mem + i * chunk_size));
    }

    a = (allocator*) malloc(sizeof(allocator));
    memcheck(a);

    a->chunk_size = chunk_size;
    a->chunks_used = 0;
    a->n = n;
    a->mem = mem;
    a->mem_end = mem + (chunk_size * (n - 1));
    a->list = list;
}

pointer myAlloc() {
    if (listIsEmpty(a->list)) {
        return NULL;
    }
    a->chunks_used++;
    header* h = getHeader(a->list);
    #ifdef DEBUG
        printf("Allocator: memory allocated %p %p; chunks_used %zu; all memory %zu\n", h->val, a->mem_end, a->chunks_used, a->n);
    #endif
    return h->val;
}

pointer myRealloc(pointer mem, size_t size) {
    assert(size < a->chunk_size);
    return mem;
}

void myFree(pointer mem) {
    a->chunks_used--;
    #ifdef DEBUG
        int flag = 0;
        for (size_t i = 0; i < a->n; i++) {
            if (mem == allocated_mem[i]) {
                flag = 1;
            }
        }
        if (!flag) {
            printf("ERROR in allocator: unknown address in free");
            exit(1);
        }
    printf("Allocator: memory freed %p; %zu; all memory %zu\n", mem, a->chunks_used, a->n);
    #endif
    addHeader(a->list, storeHeader(mem));
}

void stopAllocate() {
    free(a->mem);
    free(a->list);
    free(a);
}