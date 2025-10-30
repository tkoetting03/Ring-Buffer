#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int *buffer;
    int capacity;
    int mask;
    int head;
    int tail;
    int stored;
} ringBuffer;

void ringBuffer_init(ringBuffer *pointerStruct, int capacity) {
    pointerStruct->capacity = capacity;
    pointerStruct->mask = capacity - 1;
    pointerStruct->head = 0;
    pointerStruct->tail = 0;
    pointerStruct->stored = 0;
}


void push(ringBuffer *pointerStruct, int pushValue) {
    pointerStruct->buffer[pointerStruct->head] = pushValue;
    pointerStruct->head = (pointerStruct->head + 1) & pointerStruct->mask;
    pointerStruct->stored++;
}

void pop(ringBuffer *pointerStruct, int *outputLocation) {
    *outputLocation = pointerStruct->buffer[pointerStruct->tail];
    pointerStruct->tail = (pointerStruct->tail + 1) & pointerStruct-> mask;
    pointerStruct->stored--;
}

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

int main(void) {
    const int capacity = 16;  

    ringBuffer rb;

    ringBuffer_init(&rb, capacity);

    for (int i = 0; i < capacity; ++i) {
        int val = i * 10;
        push(&rb, val);
        printf("push: %3d  [head=%2d, tail=%2d, stored=%2d]\n",
               val, rb.head, rb.tail, rb.stored);
    }
    while (rb.stored > 0) {
        int out = 0;
        pop(&rb, &out);
        printf("pop : %3d  [head=%2d, tail=%2d, stored=%2d]\n",
               out, rb.head, rb.tail, rb.stored);
    }

    free(rb.buffer);
    return 0;
}
