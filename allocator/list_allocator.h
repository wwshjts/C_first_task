#include"ptrList.h"
#define CUSTOM_ALLOC
typedef struct{
    ptrList* list;
    pointer mem;
    size_t max_size;
    size_t memory_used;
} allocator;

typedef size_t block_header;

ptrList_node* ptrList_node_init(pointer, size_t);
allocator* start_allocate();
void* list_malloc(allocator* , size_t );
void* list_realloc(allocator*, void*, size_t);
void list_free(allocator* a, void* mem);
void stop_allocate();
