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

<img src="/images/ringbufferloop.png" alt="Buffer Ring" title="Buffer Ring 2" width="40%">

We to replicate the above behavior represented by the arrows, with each time when we increment forward in an index at index 19, we go back to index 0, ad infinitum. The easiest way to about this is to use the modulo of the size applied to the requested position, so that when when go forward 21 elements, it will be the same as going forward 1 element. We first begin by creating a pointer which points to the first element at index 0 of the buffer. We then establish how far forward we want the pointer to move with the goalPosition variable. We then set p to point to the address of the respective element that is at the index:
    $$
    \int_0^\infty e^{-x^2} dx = \frac{\sqrt{\pi}}{2}
    $$

```
int *p = &a[0];
int goalPosition = 21;
p = &buffer[goalPosition % 20];
```

