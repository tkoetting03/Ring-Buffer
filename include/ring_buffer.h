#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct ringBuffer ringBuffer;

typedef enum { noError = 0, argError = -1, capError = -2, allocError = -3, fullError = -4, emptyError = -5 } ringError;

int ringSize(ringBuffer *pointerStruct);
int ringCap(ringBuffer *pointerStruct);
bool ringFull(ringBuffer *pointerStruct);
bool ringEmpty(ringBuffer *pointerStruct);
void ringBuffer_init(ringBuffer *pointerStruct, int capacity);
void push(ringBuffer *pointerStruct, int pushValue);
void pop(ringBuffer *pointerStruct, int *outputLocation);

#endif
