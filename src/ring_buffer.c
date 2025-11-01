#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ring_buffer.h"


typedef struct {
    int *buffer;
    int capacity;
    int mask;
    int head;
    int tail;
    int stored;
} ringBuffer;

#define isInteger(x) _Generic((x), float: false, double: false, long double: false, default: true)

int ringSize(ringBuffer *pointerStruct) {
    return pointerStruct->stored;
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

void ringBuffer_init(ringBuffer *pointerStruct, int capacity) {

    if (!(capacity > 0) | !isInteger(capacity) | !((capacity & (capacity - 1) == 0))) {
        return capError;
    }
    if (!pointerStruct) {
        return argError;
    }
    
    if (!pointerStruct->buffer) {
        return allocError;
    }
    
    pointerStruct->buffer = malloc(capacity * sizeof *pointerStruct->buffer);

    pointerStruct->capacity = capacity;
    pointerStruct->mask = capacity - 1;
    pointerStruct->head = 0;
    pointerStruct->tail = 0;
    pointerStruct->stored = 0;
}


void push(ringBuffer *pointerStruct, int pushValue) {
    if (!pointerStruct | !pointerStruct->buffer) {
        return argError;
}
    if (ringFull(pointerStruct)) {
        return fullError;
}

    pointerStruct->buffer[pointerStruct->head] = pushValue;
    pointerStruct->head = (pointerStruct->head + 1) & pointerStruct->mask;
    pointerStruct->stored++;
}

void pop(ringBuffer *pointerStruct, int *outputLocation) {
    if (!pointerStruct | !pointerStruct->buffer | !outputLocation) {
            return argError;
    }
    if (ringEmpty(pointerStruct)) {
        return emptyError;
    }

    *outputLocation = pointerStruct->buffer[pointerStruct->tail];
    pointerStruct->tail = (pointerStruct->tail + 1) & pointerStruct-> mask;
    pointerStruct->stored--;
}

