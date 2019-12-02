# Queue
A low level implementation in **C** of a Queue container. Can be filled with nearly any data type.

## Version

Version **[1.0.0 (Virgin)](https://github.com/Hasenfresser/Queue/releases/tag/1.0.0)** released!


## What's a Queue?
A Queue is a dynamic data container. It can store an (theoretically) infinite or a specific number of elements of the same data type.
The elements are accessed with the **FIFO (first in first out)** principle.

New elements are *enqueued* on the back of the Queue, while the first element gets dequeued. A Queue can access its *first* and *last* element very easily.
Most Queues have also some functionalities like a *maximum size*, a *clear* function (deleting all elements) or a check if Queue is *full* or *empty*.

![QueueVisu](https://upload.wikimedia.org/wikipedia/commons/thumb/5/52/Data_Queue.svg/1920px-Data_Queue.svg.png)

Graphical visualization of a Queue.
*Source: https://upload.wikimedia.org/wikipedia/commons/thumb/5/52/Data_Queue.svg/1920px-Data_Queue.svg.png*


## Usage

This C implementation of a Queue is **not** fixed to a specific data type which can be stored in it. You can use it for *nearly* every data type.

Just copy the *Queue.c* and *Queue.h* into your project folder and include *Queue.h* in your source code.

```
#include "<optional_path/>Queue.h"
```

### Creating new Queue

*Example 1:* Creating a Queue of `double`:
```
Queue *pdQueue = newQueue(sizeof(double));
```

*Example 2:* Creating a Queue of `int`:
```
Queue *piQueue = newQueue(sizeof(int));
```

The function `Queue *newQueue(const size_t p_tSize)` gets a byte size as parameter. It is usefull to get the byte size of an element by using `sizeof`.
The function returns a pointer to the newly created Queue.

A newly created Queue can store an infinite amount of elements. You can change this later.

If anything goes wrong while creating the Queue or the byte size is zero, the returned pointer is zero (`0`).

*Alternative:* Creating a local Queue of `char` with maximum of `5` elements:
```
Queue cQueue = { sizeof(char), 5, 0, 0, 0 };
```

This method does not need the function `newQueue`. You can declare the Queue struct directly. Make sure not to mess up the parameters. The last three should always be initialized with `0`.
An explanation for all Queue struct members will follow.
For all other functions you will have to use `&cQueue` instead of just using the Queue pointer itself.
It is recommended to use the function instead because it has some error handling.

### Queue maximum

After creating a new Queue, you can edit the maximum number of elements.

*Example 1:* Set maximum number of `double` elements in Queue to `5`:
```
pdQueue->m_tMax = 5;
```

This sets the maximum number of elements in the Queue to `5`.
If the maximum number of elements is reached, no new elements can be *enqueued*.


*Example 2:* Set number of `int` elements in Queue to infinite:
```
piQueue->m_tMax = 0;
```

If set to `0`, the Queue can contain an infinte number of elements (theoretically).

The other members of the Queue structure (`m_tSize`, `m_tElems`, `m_pFirst` and `m_pLast`) should **never ever** be touched! Otherwise this could cause undefined behavior.
`m_tSize` contains the size of the data in each Queue element (node) and is automatically set while creating a new Queue.
`m_tElems` contains the number of elements (nodes) in the Queue and is calculated automatically.
`m_pFirst` and `m_pLast` contain pointers to the first and last element (Node) of the Queue which are set automatically while editing.

### Enqueuing new element into Queue

*Example 1:* Enqueuing new `double` into Queue:

```
double d = 4.5;
queueEnqueue(pdQueue, &d);
```

*Example 2:* Enqueuing new `int` into Queue and storing return value in integer for later evaluation:

```
int i = -4;
int iRet = queueEnqueue(piQueue, &i);

if(iRet == QUEUE_FULL) {
// error handling ...
    
```

The function `int queueEnqueue(Queue *const p_pQueue, void *const p_pData)` gets the Queue pointer as first argument. 

The second argument contains a void pointer to the actual data. Therefore the data could be anything. **Make sure** that the data the pointer is referencing to has the correct byte size - there is no actual check if this is correct!
If the enqueued data is bigger than the single element byte size, it will **not** be properly stored!

If any argument is an empty pointer, the function will return `QUEUE_ZP` (`-1`).
If the Queue is full, it will not push anything and returns `QUEUE_FULL` (`-2`).
If there is an error while allocating memory for the new element, the function returns `QUEUE_BADMAL` (`-3`).


### Getting first and last element of Queue

*Example 1:* Saving first `double` element of Queue in `double dFront`:
```
double dFront = *(double *)queueFront(pdQueue);
```

*Example 2:* Saving pointer to last `int` element of Queue in `int *piBack`:
```
int *piBack= (int *)queueBack(piQueue);
```

*Example 3:* Saving pointer to first `int` element of Queue in `void pointer`:
```
void *p = queueFront(piQueue);
```

The functions `void *queueFront(Queue *const p_pQueue)` and `void *queueBack(Queue *const p_pQueue)` get the Queue pointer as argument.

They will return a pointer to the first or last element of the Queue. It can be stored in a void pointer or casted to a specific data type (which usually matches with the data type the Queue stores).

If the Queue pointer or the Queue itself is empty (contains 0 elements) the functions will return a zero pointer (`0`).

### Dequeuing first element of Queue

*Example 1:* Dequeuing first `double` element of Queue:
```
queueDequeue(pdQueue);
```

*Example 2:* Dequeuing first `int` element of Queue and storing return value in integer for later evaluation:
```
int iRet = queueDequeue(piQueue);

if(iRet == QUEUE_ZP) {
// error handling
```

The function `int queueDequeue(Queue *const p_pQueue)` gets the Queue pointer as argument.
It will delete the first element of the Queue.

If the Queue pointer is empty, the function will return `QUEUE_ZP` (`-1`).


### Clearing Queue

*Example 1:* Clearing all `double` elements in Queue:
```
queueClear(pdQueue);
```

*Example 2:* Clearing all `int` elements in Queue and storing return value in integer for later evaluation:
```
int iRet = queueClear(pdSQueue);

if(iRet > 5) {
// handling when Queue had more than 5 elements...
```

The function `int queueClear(Queue *const p_pQueue)` gets the Queue pointer as argument.
It will repetitively delete the first element of the Queue until it is empty and returning the number of deleted elements.

If the Queue pointer is empty, the function will return `QUEUE_ZP` (`-1`).


### Queue flags

*Example 1:* Check if `int` Queue is empty
```
int iREt = queueIsEmpty(piQueue);

if(iRet == 0) {
// handling when Queue is empty...
```

The function `int queueIsEmpty(Queue *const p_pQueue)` gets the Queue pointer as argument.

If the Queue stores no elements, it will return `1`, otherwise `0`.
If the Queue pointer is empty, the function will return `QUEUE_ZP` (`-1`).

*Example 2:* Check if `double` Queue with a maximum of `5` elements is full
```
pdQueue->m_tMax = 5;
/* (...some pushing...) */
int iEmpty = queueIsFull(pdQueue);
```

The function `int queueIsFull(Queue *const p_pQueue)` gets the Queue pointer as argument.

If the number of elements in the Queue equals or is bigger than the maximum, it will return `1`, otherwise `0`.
If there is no maximum set (`0`), it will always return `0`.
If the Queue pointer is empty, the function will return `QUEUE_ZP` (`-1`).

## Misc
- This implementation tries to make **C** programming a little bit easier, but is also some kind of low level. So don't expect to much comfort while using it. It is recommended to check everything twice before releasing something. Empty pointers can easily become dangerous! :stuck_out_tongue_winking_eye:
- It is **not** recommended to use this implementation in **C++** (only if it has to be very perfomant with simple data types), because it has its own class for [Queues](http://www.cplusplus.com/reference/queue/queue/). This can also be used for objects and their constructors, which is a great advantage.
- This implementation only uses the standard C libraries `stdlib.h` and `string.h`, so it can be compiled on nearly any distribution.

## ToDos

- :white_check_mark: Basic implementation of all functionalities (using [Stack](https://github.com/Hasenfresser/Stack) as template)
- :white_check_mark: Implementing `main.c` with usage example 
- :white_check_mark: Completing ReadMe.md

- :negative_squared_cross_mark: Full error checking
- :negative_squared_cross_mark: Adding `attach` functionality
- :negative_squared_cross_mark: Adding `duplicate` functionality
- :negative_squared_cross_mark: Adding `replace` functionality
- :negative_squared_cross_mark: Getting some feedback 

## Bugs and Issues

...if you find some, just let me know! :wink:


Greetings,
Hasenfresser
