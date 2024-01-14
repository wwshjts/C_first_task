#define BASE_STACK_CAPACITY 10

typedef struct {
    int* data;
    size_t size;
    size_t capacity;
} Stack;

// typical functions
void stackInit(Stack* st);
void stackResize(Stack* st);
int stackPeek(Stack* st);
int stackPop(Stack*  st);
size_t stackSize(Stack* st);
int stackIsEmpty(Stack* st);

// unique functions for this data structure
void stackFree(Stack* st);
void stackAdd(Stack* st, int item);
void stackShrink(Stack* st);
void stackPrint(Stack* st);
