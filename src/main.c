#include <stdio.h>
#include "ring_buffer.h"
#include "ring_buffer.c"


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