/**
 * @file Queue.c
 * @author Hasenfresser
 * @date 2019-12-02
 * @version 1.0.0 (Virgin)
 *
 * @brief Source file of all Queue functions.
 */

#include "Queue.h"

Queue *queueNew(const size_t p_tSize) {
    // if element (Node) size is zero, return zero pointer
    if(p_tSize == QUEUE_EMPTY) {
        return QUEUE_EMPTY;
    }

    // allocating memory for new Queue and initialize everything with 0
    Queue *pQueue = (Queue *)malloc(sizeof(Queue));

    // check allocation, return zero pointer if failed
    if(!pQueue) {
        return QUEUE_EMPTY;
    }

    // set initial values of new Queue
    pQueue->m_pFirst = QUEUE_EMPTY;
    pQueue->m_pLast = QUEUE_EMPTY;
    pQueue->m_tMax = QUEUE_EMPTY;
    pQueue->m_tElems = QUEUE_EMPTY;
    pQueue->m_tSize = p_tSize;

    // returning pointer of new Queue
    return pQueue;
}

int queueIsEmpty(Queue *const p_pQueue) {
    // if Queue pointer is empty, return -1
    if(!p_pQueue) {
        return QUEUE_ZP;
    }

    // return 1 if first element of Queue is empty, otherwise 0
    return (!p_pQueue->m_pFirst);
}

int queueIsFull(Queue *const p_pQueue) {
    // if Queue pointer is empty, return zero pointer error
    if(!p_pQueue) {
        return QUEUE_ZP;
    }

    // return 1 if maximum is set and number of elements is equal or greater than maximum, otherwise 0
    return (p_pQueue->m_tMax && p_pQueue->m_tElems >= p_pQueue->m_tMax);
}

void *queueFront(Queue *const p_pQueue) {
     // if Queue pointer is empty or Queue is empty, return empty pointer
    if(!p_pQueue || !p_pQueue->m_pFirst) {
        return QUEUE_EMPTY;
    }

    // return pointer of first element in Queue
    return p_pQueue->m_pFirst->m_pData;
}

void *queueBack(Queue *const p_pQueue) {
     // if Queue pointer is empty or Queue is empty, return empty pointer
    if(!p_pQueue || !p_pQueue->m_pFirst) {
        return QUEUE_EMPTY;
    }

    // return pointer of last element in Queue
    return p_pQueue->m_pLast->m_pData;
}

int queueEnqueue(Queue *const p_pQueue, void *const p_pData) {
    // if Queue or data pointer is empty, return zero pointer error
    if(!p_pQueue || !p_pData) {
        return QUEUE_ZP;
    }
    // check if Queue is full, return Queue full error
    else if(queueIsFull(p_pQueue)) {
        return QUEUE_FULL;
    }

    // allocating memory for new Queue element (Node) and initialize with zero
    QueueElem *pNode = (QueueElem *)malloc(sizeof(QueueElem));

    // check allocation, return bad memory allocation error if failed
    if(!pNode) {
        return QUEUE_BADMAL;
    }

    // allocating memory for data in new Node and initialize with 0
    pNode->m_pData = malloc(p_pQueue->m_tSize);

    // check allocation, clear allocated memory and return bad memory allocation error if failed
    if(!pNode->m_pData) {
        free(pNode);
        return QUEUE_BADMAL;
    }

    // copying data from data pointer parameter into node data pointer using byte size of one element
    memcpy(pNode->m_pData, p_pData, p_pQueue->m_tSize);

    // if Queue is empty, new element has no successor
    if(!p_pQueue->m_pFirst) {
        p_pQueue->m_pFirst = pNode;
        p_pQueue->m_pLast = pNode;
    }
    else {
        p_pQueue->m_pLast->m_pNext = pNode;
        p_pQueue->m_pLast = pNode;
    }

    // increment number of Queue elements
    ++p_pQueue->m_tElems;

    // Return number of pushed bytes
    return p_pQueue->m_tSize;
}

int queueDequeue(Queue *const p_pQueue) {
    // if Queue pointer or Queue is empty, return QUEUE_ZP
    if(!p_pQueue || queueIsEmpty(p_pQueue)) {
        return QUEUE_ZP;
    }

    // if Queue has only one element (Node)
    if(p_pQueue->m_pFirst == p_pQueue->m_pLast) {
        // freeing space of element (Node and data)
        free(p_pQueue->m_pFirst->m_pData);
        free(p_pQueue->m_pFirst);

        // setting pointer to first and last of Queue element (Node) to zero
        p_pQueue->m_pFirst = QUEUE_EMPTY;
        p_pQueue->m_pLast = QUEUE_EMPTY;

        // setting number of elements in Queue to zero
        p_pQueue->m_tElems = 0;
    }
    else {
        // creating temporary pointer with "old" first element
        QueueElem *pNode = p_pQueue->m_pFirst;

        // make second element the "new" first element
        p_pQueue->m_pFirst = pNode->m_pNext;

        // freeing space of "old" first element (Node and data)
        free(pNode->m_pData);
        free(pNode);

        // decrementing number of Queue elements
        --p_pQueue->m_tElems;
    }

    // Return number of popped bytes
    return p_pQueue->m_tSize;
}

int queueClear(Queue *const p_pQueue) {
    // if Queue pointer or Queue is empty, return QUEUE_ZP
    if(!p_pQueue) {
        return QUEUE_ZP;
    }

    // setting up counter
    int iCounter = QUEUE_EMPTY;

    // popping Queue until it is empty and increment counter
    while(!queueIsEmpty(p_pQueue)) {
        queueDequeue(p_pQueue);
        ++iCounter;
    }

    // returning counter (number of deleted elements)
    return iCounter;
}
