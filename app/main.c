#include <stdio.h>
#include "include/ring_buffer.h"
#include "src/ring_buffer.c"


int main(void) {
    const int capacity = 16;  

    ringBuffer rb;

    ringBuffer_init(&rb, capacity);

    for (int i = 0; i < capacity; ++i) {
        int val = i * 10;
        push(&rb, val);
        printf("push: %d \n", val);
    
        for (int j = 0; j < capacity; ++j) {
            printf("%d, ", rb.buffer[j]);
        }

    }
    return 0;
}