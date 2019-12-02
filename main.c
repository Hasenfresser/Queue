
/**
 * @file main.c
 * @author Hasenfresser
 * @date 2019-12-02
 * @version 1.0.0 (Virgin)
 *
 * @brief Main file for testing purposes
 *
 * This file can be used to include and test the Queue implementation.
 * A small example is already written.
 *
 * The example stores and displays every parameter (per character) using the Queue.
 * When enabling Queue maximum (MAX), every input parameter will be trimmed.
 */

#include "Queue.h"

#include <stdio.h>

#define MAX 10 /**< Maximum elements in Queue */
#define CNT 7 /**< Number of elements printed */

int main(const int p_iArgC, char *p_apcArgV[]) {
    // creating new Queue
    Queue *pcQueue = queueNew(sizeof(char));

    // set maximum to MAX
    pcQueue->m_tMax = MAX;

    // iterate throug all input parameters
    int iC = 1;

    while(iC < p_iArgC) {
        printf("##### ENQUEUE #####\n");

        // iterate through all characters of input parameter
        while(*p_apcArgV[iC] != '\0') {
            // enqueue every single char
            int iRet = queueEnqueue(pcQueue, p_apcArgV[iC]);

            // displaying last element, return value and some flags and stats of Queue
            printf("%c, bytes enqueued: %d, full: %d, empty: %d, size: %d\n", *(char *)queueBack(pcQueue), iRet, queueIsFull(pcQueue), queueIsEmpty(pcQueue), pcQueue->m_tElems);

            ++p_apcArgV[iC];
        }

        printf("##### DEQUEUE #####\n");

        int iC2 = CNT;

        // iterate through all elements of Queue until it's empty or iC2 is zero
        while(!queueIsEmpty(pcQueue) && iC2--) {
            // Printing first Element of Queue
            printf("%c, ", *(char *)queueFront(pcQueue));

            // dequeuing first Element of Queue
            int iRet = queueDequeue(pcQueue);

            // displaying return value and some flags and stats of Queue
            printf("%d bytes popped, full: %d, empty: %d, size: %d\n", iRet, queueIsFull(pcQueue), queueIsEmpty(pcQueue), pcQueue->m_tElems);
        }

        // clearing Queue
        int iRet = queueClear(pcQueue);

        // displaying number of deleted elements and some flags and stats of Queue
        printf("Queue cleared (%d elements deleted), full: %d, empty: %d, size: %d\n\n", iRet, queueIsFull(pcQueue), queueIsEmpty(pcQueue), pcQueue->m_tElems);

        ++iC;
    }

    // destroying Queue
    free(pcQueue);

    exit(EXIT_SUCCESS);
}


