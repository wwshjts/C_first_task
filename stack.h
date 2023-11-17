#define BASE_STACK_CAPACITY 10

typedef struct {
    int* data;
    size_t size;
    size_t capacity;
} Stack;

void stackInit(Stack* st);
void stackFree(Stack* st);
void stackAdd(Stack* st, int item);
int stackSeek(Stack* st);
int stackPop(Stack*  st);
void stackShrink(Stack* st);
void stackPrint(Stack* st);
