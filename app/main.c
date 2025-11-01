#include <stdio.h>
#include "/workspaces/Ring-Buffer/include/ring_buffer.h"
#include "/workspaces/Ring-Buffer/src/ring_buffer.c"


int main(void) {
    const int capacity = 8;  

    ringBuffer rb;


    ringBuffer_init(&rb, capacity);

    for (int i = 0; i < capacity; ++i) {
        int val = i * 10;
        push(&rb, val);
        printf("push: %d \n", val);
    }

    for (int j = 0; j < rb.capacity; ++j) {
        printf("%d, ", rb.buffer[j]);
    }


    return 0;
}