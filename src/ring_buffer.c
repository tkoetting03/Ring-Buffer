#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "/workspaces/Ring-Buffer/include/ring_buffer.h"


typedef struct ringBuffer { // create the ringBuffer "object" (struct)
    int *buffer; // pointer to the ring buffer in memory
    int capacity; // capacity of the ring buffer
    int mask; // mask for bitwise ANDing in place of modulo
    int head; // pointer to next index to be written in
    int tail; // pointer to next index to be popped
    int stored; // number of elements stored in the buffer
} ringBuffer;

#define isInteger(x) _Generic((x), float: true, double: true, long double: true, default: false) // creates a function which checks the type of a variable and returns ture if it is a decimal and false if it is an integer

int ringSize(ringBuffer *pointerStruct) { //function that returns the number of stored elements in the buffer
    return pointerStruct->stored;
}

int isPowerOfTwo(int x) { // function that checks if a number is expressable is a power of two (x=2^n)
    return x > 0 && (x & (x - 1)) == 0;
}

int ringCap(ringBuffer *pointerStruct) { // function that returns the buffer's maximum element capacity
    return pointerStruct->capacity;
}

bool ringFull(ringBuffer *pointerStruct) { // function that returns TRUE if the buffer is full and FALSE if it is not full
    return pointerStruct->capacity == pointerStruct->stored;
}

bool ringEmpty(ringBuffer *pointerStruct) { // function that returns TRUE if the buffer is empty and FALSE if it is not empty
    return pointerStruct->stored == 0;
}

void destroyRing(ringBuffer *pointerStruct) {  // function that erases the buffer
    free(pointerStruct->buffer);
    free(pointerStruct);
}

void printRing(ringBuffer *pointerStruct) {
    if (ringEmpty(pointerStruct)) {
        printf("The Buffer is Empty\n");
    }
    else{
        for (int j = 0; j < pointerStruct->stored; ++j) {
            int index = (pointerStruct->tail + j) & pointerStruct->mask;
            printf("%d", pointerStruct->buffer[index]);
            if (j + 1 < pointerStruct->capacity) {
                printf(", ");
            }
        }
        printf("\n");
    }
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

ringError pushOver(ringBuffer *pointerStruct, int pushValue) {

    pointerStruct->buffer[pointerStruct->head] = pushValue;
    pointerStruct->head = (pointerStruct->head + 1) & pointerStruct->mask;
    
    return noError;

}

ringError pop(ringBuffer *pointerStruct, int *outputLocation) {
    if (!pointerStruct || !pointerStruct->buffer || !outputLocation) {
            return argError;
    }
    if (ringEmpty(pointerStruct)) {
        return emptyError;
    }

    *outputLocation = pointerStruct->buffer[pointerStruct->tail];
    pointerStruct->buffer[pointerStruct->tail] = 0;
    pointerStruct->tail = (pointerStruct->tail + 1) & pointerStruct-> mask;
    pointerStruct->stored--;

    return noError;
}

