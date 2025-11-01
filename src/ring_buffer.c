#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "/workspaces/Ring-Buffer/include/ring_buffer.h"


typedef struct ringBuffer {
    int *buffer;
    int capacity;
    int mask;
    int head;
    int tail;
    int stored;
} ringBuffer;

#define isInteger(x) _Generic((x), float: true, double: true, long double: true, default: false)

int ringSize(ringBuffer *pointerStruct) {
    return pointerStruct->stored;
}

int isPowerOfTwo(int x) {
    return x > 0 && (x & (x - 1)) == 0;
}

int ringCap(ringBuffer *pointerStruct) {
    return pointerStruct->capacity;
}

bool ringFull(ringBuffer *pointerStruct) {
    return pointerStruct->capacity == pointerStruct->stored;
}

bool ringEmpty(ringBuffer *pointerStruct) {
    return pointerStruct->stored == 0;
}

void destroyRing(ringBuffer *pointerStruct) {
    free(pointerStruct->buffer); free(pointerStruct);
}

ringError ringBuffer_init(ringBuffer *pointerStruct, size_t capacity) {

    if (capacity < 0) {
        return capError;
    }

    if (isInteger(capacity)) {
        return capError;
    }

    if (!isPowerOfTwo(capacity)) {
        return capError;
    }
    
    if (!pointerStruct) {
        return argError;
    }
    
    pointerStruct->buffer = malloc(capacity * (sizeof *pointerStruct->buffer));
    pointerStruct->capacity = capacity;
    pointerStruct->mask = capacity - 1;
    pointerStruct->head = 0;
    pointerStruct->tail = 0;
    pointerStruct->stored = 0;

    if (!pointerStruct->buffer) {
        return allocError;
    }


    return noError;
}


ringError push(ringBuffer *pointerStruct, int pushValue) {
    if (!pointerStruct | !pointerStruct->buffer) {
        return argError;
}
    if (ringFull(pointerStruct)) {
        return fullError;
}

    pointerStruct->buffer[pointerStruct->head] = pushValue;
    pointerStruct->head = (pointerStruct->head + 1) & pointerStruct->mask;
    pointerStruct->stored++;

    return noError;
}

ringError pop(ringBuffer *pointerStruct, int *outputLocation) {
    if (!pointerStruct | !pointerStruct->buffer | !outputLocation) {
            return argError;
    }
    if (ringEmpty(pointerStruct)) {
        return emptyError;
    }

    *outputLocation = pointerStruct->buffer[pointerStruct->tail];
    pointerStruct->tail = (pointerStruct->tail + 1) & pointerStruct-> mask;
    pointerStruct->stored--;

    return noError;
}

