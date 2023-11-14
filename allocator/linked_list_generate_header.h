#define LINKED_LIST_GENERATE_HEADER(NAME, T)\
typedef struct _node_##T{\
    struct _node_##T* next;\
    struct _node_##T* prev;\
    T val;\
    size_t size;\
} NAME##_node;\
typedef struct{\
    NAME##_node* head;\
    NAME##_node* tail;\
    int size;\
} NAME;\
void NAME##_init(NAME * list);\
void NAME##_add_to_head(NAME * list, NAME##_node* v);\
void NAME##_add_to_tail(NAME * list,NAME##_node* v);\
void NAME##_insert_prev(NAME * list, NAME##_node* curr, NAME##_node * node);\
NAME##_node* NAME##_pop_head(NAME * list);\
NAME##_node* NAME##_pop_tail(NAME * list);\
int NAME##_is_empty(NAME * list);\
void NAME##_free(NAME * list);\
void NAME##_delete(NAME *, NAME##_node*);
