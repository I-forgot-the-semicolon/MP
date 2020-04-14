#ifndef __DEBUG_HELPER__
#define __DEBUG_HELPER__

#include <stdio.h>
#include <stdlib.h>

#define DEBUG

typedef struct
{
    size_t allocatedMemory;
    size_t freedMemory;
    size_t *sizeIndex;
    int pos;
} Memory;

Memory memoryDebug;

void *allocate(size_t size, char *tag);
void *reallocate(void *pointer, size_t size, char *tag);
void deallocate(void *pointer, char *tag);
void showMemory();
#endif