#include "debug.h"

void *allocate(size_t size, char *tag)
{
    memoryDebug.pos++;
    memoryDebug.sizeIndex = realloc(memoryDebug.sizeIndex, sizeof(size_t)*memoryDebug.pos);

    memoryDebug.sizeIndex[memoryDebug.pos-1] = size;
    memoryDebug.allocatedMemory += size;
    #ifdef DEBUG
    printf("-----------------------------\n");
    printf("Allocating %lu bytes from %s...\n", size, tag);
    printf("Total allocated bytes: %lu\n", memoryDebug.allocatedMemory);
    printf("Items allocated: %d\n", memoryDebug.pos);
    #endif
    return malloc(size);
}

void *reallocate(void *pointer, size_t size, char *tag)
{
    int deltaBytes = size - memoryDebug.sizeIndex[memoryDebug.pos-1];
    memoryDebug.sizeIndex[memoryDebug.pos-1] += deltaBytes;
    memoryDebug.allocatedMemory += deltaBytes;
    #ifdef DEBUG
    printf("-----------------------------\n");
    printf("Reallocation %lu bytes from %s...\n", size, tag);
    printf("Delta bytes is: %d\n", deltaBytes);
    printf("Total allocated bytes: %lu\n", memoryDebug.allocatedMemory);
    #endif
    return realloc(pointer, size);
}

void deallocate(void *pointer, char *tag)
{
    size_t size = memoryDebug.sizeIndex[memoryDebug.pos-1];
    memoryDebug.freedMemory += size;
    memoryDebug.allocatedMemory -= size;
    memoryDebug.pos--;
    memoryDebug.sizeIndex = realloc(memoryDebug.sizeIndex, sizeof(size_t)*memoryDebug.pos);

    #ifdef DEBUG
    printf("-----------------------------\n");
    printf("Deallocating %lu bytes from %s...\n", size, tag);
    printf("Total allocated bytes: %lu\n", memoryDebug.allocatedMemory);
    printf("Items allocated: %d\n", memoryDebug.pos);
    #endif
    //printf("Freed bytes: %lu\n", memoryDebug.freedMemory);

    free(pointer);
}

void showMemory()
{
    printf("----------------------------------------------------\n");
    printf("Total allocated bytes: %lu\n", memoryDebug.allocatedMemory);
    printf("Items allocated: %d\n", memoryDebug.pos);
}