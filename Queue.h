/**
 * @file Queue.h
 * @author Hasenfresser
 * @date 2019-12-02
 * @version 1.0.0 (Virgin)
 *
 * @brief Header file of all Queue functions and structures.
 *
 * This is a low level implementation of a Queue in C programming language.
 * Every Queue can be initialized with a specific element size, therefore any data type can be stored in the Queue.
 *
 * The usage is very simple, but has also very little comfortableness for wrong usage or error handling.
 *
 * @see https://github.com/Hasenfresser/Queue
 */

#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h> /**< for memory allocations */
#include <string.h> /**< for memcpy and size_t */

/**
 * @brief Enumeration with all error and initial values.
 */
enum {
    QUEUE_EMPTY = 0, /**< initial value for Queue members */
    QUEUE_ZP = -1, /**< error value if parameter is zero pointer */
    QUEUE_BADMAL = -2, /**< error value if memory allocation failed */
    QUEUE_FULL = -3 /**< error value if Queue is full (no push) */
};

/**
 * @brief Structure for single element (Node) in Queue.
 */
typedef struct QueueElem {
    void *m_pData; /**< void pointer to element data */
    struct QueueElem *m_pNext; /**< pointer to next element (Node) */
} QueueElem;

/**
 * @brief Structure for Queue. Pointer to this is used as the actual Queue in the program.
 */
typedef struct Queue {
    size_t m_tSize; /**< Byte size of each element in Queue, editing this is not recommended */
    size_t m_tMax; /**< Maximum number of elements (Nodes) in Queue */
    size_t m_tElems; /**< Number of elements (Nodes) in Queue, do NOT edit! */
    QueueElem *m_pFirst; /**< Pointer to first element (Node) in Queue, do NOT edit! */
    QueueElem *m_pLast; /**< Pointer to last element (Node) in Queue, do NOT edit! */
} Queue;

/**
 * @brief Creates a new Queue with a specific element size
 * @param p_tSize: size_t with element size in Queue
 * @return Pointer to new Queue; when creation failed or byte size is zero, pointer is zero
 */
extern Queue *queueNew(const size_t p_tSize);

/**
 * @brief Checks if Queue is empty
 * @param p_pQueue: Pointer to actual Queue
 * @return 1 when Queue is empty, otherwise 0 or error value
 *
 * If Queue pointer is zero, the function returns QUEUE_ZP.
 */
extern int queueIsEmpty(Queue *const p_pQueue);

/**
 * @brief Checks if Queue is full
 * @param p_pQueue: Pointer to actual Queue
 * @return 1 when Queue is full otherwise 0 or error value
 *
 * If Queue pointer is zero, the function returns QUEUE_ZP.
 */
extern int queueIsFull(Queue *const p_pQueue);

/**
 * @brief Returns front element of the Queue
 * @param p_pQueue: Pointer to actual Queue
 * @return Pointer to front element of Queue or error value
 *
 * If Queue pointer is zero, the function returns QUEUE_ZP.
 */
extern void *queueFront(Queue *const p_pQueue);

/**
 * @brief Returns back element of the Queue
 * @param p_pQueue: Pointer to actual Queue
 * @return Pointer to back element of Queue or error value
 *
 * If Queue pointer is zero, the function returns QUEUE_ZP.
 */
extern void *queueBack(Queue *const p_pQueue);

/**
 * @brief Pushes element onto end of Queue.
 * @param p_pQueue: pointer to actual Queue
 * @param p_pData: pointer to new element (Node) data
 * @return Number of bytes pushed or error value
 *
 * If any parameter pointer is zero, the function returns QUEUE_ZP.
 * If something with memory allocation went wrong, the functions returns QUEUE_BADMAL.
 * If Queue reached its maximum number of elements, the function returns QUEUE_FULL.
 */
extern int queueEnqueue(Queue *const p_pQueue, void *const p_pData);

/**
 * @brief Pops (deletes) top element of Queue.
 * @param p_pQueue: pointer to actual Queue
 * @return Number of bytes popped or error value
 *
 * If Queue pointer is zero, the function returns QUEUE_ZP.
 */
extern int queueDequeue(Queue *const p_pQueue);

/**
 * @brief Pops (deletes) all element of Queue.
 * @param p_pQueue: pointer to actual Queue
 * @return Number of elements deleted or error value

 * If Queue pointer is zero, the function returns QUEUE_ZP.
 */
extern int queueClear(Queue *const p_pQueue);

#endif // QUEUE_H
