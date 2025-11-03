#include <stdio.h>
#include "/workspaces/Ring-Buffer/include/ring_buffer.h"
#include "/workspaces/Ring-Buffer/src/ring_buffer.c"


int main(void) {
    const int capacity = 8;  

    ringBuffer rb;


    ringBuffer_init(&rb, capacity);

    for (int i = 0; i < capacity + 2; ++i) {
        int val = i * 10;
        if (rb.stored == rb.capacity) {
            if (pushOver(&rb, val) == noError) {
                printf("Push: %d \n", val);
        }
        else {
            printf("Error!\n");
    }
        }
        else {
            if (push(&rb, val) == noError) {
                printf("Push: %d \n", val);
            }
            else {
                printf("Error!\n");
            }
        }
        
    }
    printf("Elements Stored: %d\n", rb.stored);    
    printRing(&rb);

    for (int k = 0; k < rb.capacity; ++k) {
        int output;
        if (pop(&rb, &output) == noError) {
            printf("Pop: %d\n", output);
        }
        else {
            printf("Error!\n");
        }
    }
    printf("Elements Stored: %d\n", rb.stored);    
    printRing(&rb);


    return 0;
}