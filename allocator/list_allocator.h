#include"ptrList.h"
#define CUSTOM_ALLOC

typedef struct{
    ptrList* list;
    pointer mem;
    size_t n;
    size_t memory_used;
    size_t chunk_size;
} allocator;


ptrList_node* ptrList_node_init(pointer, size_t);
allocator* start_allocate();
void* list_malloc(allocator* );
void* list_realloc(allocator*, pointer);
void list_free(allocator* a, void* mem);
void stop_allocate();
