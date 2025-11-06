#include <stdio.h>
#include "/workspaces/Ring-Buffer/include/ring_buffer.h"
#include "/workspaces/Ring-Buffer/src/ring_buffer.c"


int main(void) {
    const int capacity = 8;  // setting the capacity of the ring buffer to be 8

    ringBuffer rb; // creating a ringBuffer variable rb


    ringBuffer_init(&rb, capacity); // initializing the ringBuffer variable rb

    for (int i = 0; i < capacity + 2; ++i) { // creating a loop that iterates two times more than the capacity of the ring buffer
        int val = i * 10; // setting the pushed values to be 10 times whatever i is
        if (rb.stored == rb.capacity) { // if the number of stored element is the same as the ring buffer capacity
            if (pushOver(&rb, val) == noError) { // push the value using the pushOver function to overwrite the previous value
                printf("Push: %d \n", val); // if there is no error print "Push: (value pushed)"
        }
            else {
                printf("Error!\n"); // if there is an error print "Error!"
    }
        }
        else { // if the number of stored elements is not equal to the ring buffer capacity
            if (push(&rb, val) == noError) { // push the value to the buffer
                printf("Push: %d \n", val);  // if there is no error print "Push: (value pushed)"
            }
            else {
                printf("Error!\n"); // if there is an error print "Error!"
            }
        }
        
    }
    printf("Elements Stored: %d\n", rb.stored); // print the number of elements stored in the ring buffer
    printRing(&rb); // print the elements in the ring in sequential order

    for (int k = 0; k < rb.capacity; ++k) { // creating a loop that iterates until k is the same size as the ring buffer capacity
        int output; // creates an output variable for the popped element to be stored
        if (pop(&rb, &output) == noError) { // pop the next element and store it at the address of output
            printf("Pop: %d\n", output); // if there is no error print "Pop: (value popped)"
        }
        else {
            printf("Error!\n"); // if there is an error print "Error!"
        }
    }
    printf("Elements Stored: %d\n", rb.stored); // print the number of elements stored in the ring buffer
    printRing(&rb); // print the elements in the ring in sequential order
    destroyRing(rb.buffer);

    return 0;
}