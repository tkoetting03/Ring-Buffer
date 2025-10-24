# Ring Buffer

## Introduction

In this repository I am going to be describing the code and concepts relevant to this project. 

### Creating the Ring Buffer

Below we have a graphical representation of a ring buffer. This is a buffer with its beginning and end "linked" so that traversing the buffer results in going "around the loop" per-se.

<img src="/images/ringbufferblank.png" alt="Buffer Ring" title="Buffer Ring" width="40%">

We begin by making the ring buffer as just a normal buffer, or also known as an array. 

<img src="/images/ringbufferconverted.png" alt="Buffer Ring" title="Buffer Ring 2" width="40%">

Let's say our buffer has 20 blank elements indexed in sequential order from 0-19. We need a new straight array to mimic our conceptual array, so we set the buffer size to be 20, and initialize the first & all elements to be 0.


```
int bufferSize = 20;
int buffer[bufferSize] = {0};
```
For this first ring buffer we will use the most basic array creation methods at first and move onto more complex methods as we progress. 

<img src="/images/ringbufferloop.png" alt="Buffer Ring" title="Buffer Ring 2" width="60%">

To replicate the above behavior represented by the arrows, with each time when we increment forward in an index at index 19, we go back to index 0, ad infinitum. The easiest way to about this is to use the modulo of the size applied to the requested position, so that when when go forward 21 elements, it will be the same as going forward 1 element. We first begin by creating a pointer which points to the first element at index 0 of the buffer. We then establish how far forward we want the pointer to move with the goalPosition variable. We then set p to point to the address of the respective element that is at the index:
    
$\text{Index} = 21\mod{20} = 1$

So we then can go to the buffer at index 1.

```
int *p = &a[0];
int goalPosition = 21;
p = &buffer[goalPosition % 20];
```

Unfortunately though when working with constraints for embedded systems, using modulo is resource intensive. Modulo uses division to find remainders, at a low level it uses iterative compare, subtract, and shift steps repeatedly and often is only able to be completed once per clock cycle resulting in high latency. So we need to find a more efficient way to effectively take the modulo of a requested position movement by the size of the buffer. 

Our most viable alternative is the bitwise AND. This requires more components and has some trick restrictions but is significantly faster. The big asterisk is that the capacity the buffer has must be a power of 2. So if we adjust our original buffer size we can start with this new buffer looping technique. Let's use 16. 

<img src="/images/ringbufferloop16.png" alt="Buffer Ring" title="Buffer Ring 2" width="60%">

We need to define some new variables,

```
int bufferCapacity = 16;
int bufferMask = bufferCapacity - 1;
```

The goal of finding a mask is finding a number which when bitwise ANDed with the buffer capacity will produce all 0's, for example, our mask is 15 because if you look at the resulting binary from the AND operation we get:

```
    0001_0000 (16)
    0000_1111 (15)
&____________
    0000_0000 (0)
```

We do this since using modulo when

$\text{Index} = 16\mod{15} = 1$

We get a result of one, but assuming that the mask (15) is offset from the real modulo value that would be used, we can get a fairly straight forward modulo substitute. So in reality our operation of bitwise ANDing 16 & 15 is the same as:

$\text{Index} = 16\mod{16} = 0$

For example, if we want to traverse 17 elements, so effectively one position forward after completing one full "loop", we can see that the result of bitwise ANDing the binary representations of 17 and 15 together is 1. 


```
    0001_0001 (17)
    0000_1111 (15)
&____________
    0000_0001 (1)
```

And so on. 

