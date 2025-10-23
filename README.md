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
