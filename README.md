# Ring Buffer

## Introduction

In this repository I am going to be describing the code and concepts relevant to this project. 

## Creating the Ring Buffer

Below we have a graphical representation of a ring buffer. This is a buffer with its beginning and end "linked" so that traversing the buffer results in going "around the loop" per-se.

<img src="/images/ringbufferblank.png" alt="Buffer Ring" title="Buffer Ring" width="40%">

We begin by making the ring buffer as just a normal buffer, or also known as an array. 

<img src="/images/ringbufferconverted.png" alt="Buffer Ring" title="Buffer Ring 2" width="40%">

Let's say our buffer has 20 blank elements indexed in sequential order from 0-19. We need a new straight array to mimic our conceptual array, so we set a macro for the buffer size to be 20, and initialize the first & all elements to be 0.


```
#define BUFFER_SIZE 20
int buffer[BUFFER_SIZE] = {0};
```
For this first ring buffer we will use the most basic array creation methods at first and move onto more complex methods as we progress. 

<img src="/images/ringbufferloop.png" alt="Buffer Ring" title="Buffer Ring 2" width="60%">

To replicate the above behavior represented by the arrows, with each time when we increment forward in an index at index 19, we go back to index 0, ad infinitum. The easiest way to about this is to use the modulo of the size applied to the requested position, so that when when go forward 21 elements, it will be the same as going forward 1 element. We first begin by creating a pointer which points to the first element at index 0 of the buffer. We then establish how far forward we want the pointer to move with the goalPosition variable. We then set p to point to the address of the respective element that is at the index:
    
$\text{Index} = 21\mod{20} = 1$

So we then can go to the buffer at index 1.

```
int *p = &buffer[0];
int goalPosition = 21;
p = &buffer[goalPosition % 20];
```

Unfortunately though when working with constraints for embedded systems, using modulo is resource intensive. Modulo uses division to find remainders, at a low level it uses iterative compare, subtract, and shift steps repeatedly and often is only able to be completed once per clock cycle resulting in high latency. So we need to find a more efficient way to effectively take the modulo of a requested position movement by the size of the buffer. 

Our most viable alternative is the bitwise AND. This requires more components and has some trick restrictions but is significantly faster. The big asterisk is that the capacity the buffer has must be a power of 2. So if we adjust our original buffer size we can start with this new buffer looping technique. Let's use 16. 

<img src="/images/ringbufferloop16.png" alt="Buffer Ring" title="Buffer Ring 2" width="60%">

We need to define a new variable and redefine our original BUFFER_SIZE macro to fit our power of 2 constraints,

```
#define BUFFER_SIZE 16
int bufferMask = BUFFER_SIZE - 1;
```
We can describe our mask as the following: mathematically:

$\text{x AND }(\text{Mask}) = x\mod({\text{Buffer Size}}) $

Or

$\text{x AND }(\text{Buffer Size} -1) = x\mod({\text{Buffer Size}}) $

For example, if we want to traverse 17 elements, so effectively one position forward after completing one full "loop", we can see that the result of bitwise ANDing the binary representations of 17 and 15 together is 1. 


```
    0001_0001 (17)
    0000_1111 (15)
&____________
    0000_0001 (1)
```

And so on. We can thus implement the following C code:

```
int *p = &buffer[0];
int goalPosition = 17;
p = &buffer[goalPosition & bufferMask];
```
And put it all together to get

```
#define BUFFER_SIZE 16
int buffer[BUFFER_SIZE] = {0};
int *p = &buffer[0];
int goalPosition = 17;
int bufferMask = BUFFER_SIZE - 1;
p = &buffer[goalPosition & bufferMask];
```

This is a greately simplified program but it gets the job done. Throwing together a quick C program we will write

```
#include <stdio.h>


int main() {


    #define BUFFER_SIZE 16
    int buffer[BUFFER_SIZE] = {0};
    int *p = &buffer[0];
    buffer[1] = 25;
    int goalPosition = 17;
    int bufferMask = BUFFER_SIZE - 1;
    p = &buffer[goalPosition & bufferMask];

    printf("%d\n", *p);

return 0;
}
```

Which gives us the output:

```
25
```

## Reading and Writing to the Ring Buffer

Our program works but it isn't, well, very useful, we can't really write or read intuitive we have to alter the code each time to print a value that the pointer points to in the buffer. First of all lets start by using structs to create an "object" which describes the buffer, its variables, and its pointers. 

```
struct ringBuffer {
    int *buffer;
    int capacity = 16;
    int head = 0;
    int tail = 9;
    int stored = 9;
}
```

Our pointer, "buffer", points to the first element in the buffer in memory, 

<img src="/images/structbuffernew.png" alt="Buffer Ring" title="Buffer Ring 2" width="60%">

We also have our capacity, which is the number of elements we can store in the buffer, our "head"; which is the index where our next write will occur, our "tail"; which is the index where our next read will occur, and "stored"; which is the number of elements stored in the buffer (maximum of 16).

We now must figure out how we want to treat our elements when read and when written. Our buffer serves only as a temporary position for data so it can be read once and then popped off of the buffer. We also want to be able to push (write) new data to elements. This makes the ring buffer similar to a FIFO (first in first out) queue data structure. This means that our oldest element is at the tail, while our newest element is just before head. 

<img src="/images/headtailbuffer.png" alt="Buffer Ring" title="Buffer Ring" width="60%">
