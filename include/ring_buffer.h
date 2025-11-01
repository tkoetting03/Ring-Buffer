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
ringError ringBuffer_init(ringBuffer *pointerStruct, size_t capacity);
ringError push(ringBuffer *pointerStruct, int pushValue);
ringError pop(ringBuffer *pointerStruct, int *outputLocation);

#endif