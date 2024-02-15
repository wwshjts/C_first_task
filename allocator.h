#pragma once
#include "types.h"

void startAllocate(size_t chunk_size, size_t n);
pointer myAlloc();
pointer myRealloc(pointer);
void myFree(pointer mem);
void stopAllocate();