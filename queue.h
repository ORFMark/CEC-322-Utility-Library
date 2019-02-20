/*
 * File: queue.h
 * Project: Header Library  development for CEC320
 * Author: Mark Burrell
 * Version: 1.0 Tuesday February 19, 2019
 * Copywrite (c) 2019 Mark Burrell, all rights reserved
 * Repository: https://github.com/ORFMark/CEC-322-Utility-Library
 */

#ifndef MRBUTIL_QUEUE_H_
#define MRBUTIL_QUEUE_H_
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

#define QUEUESIZE 16
typedef struct node{
	struct node* next;
	uint32_t data;
} queueNode;

typedef struct{
	queueNode* head;
	queueNode* tail;
        uint8_t allocatedNodes;
        queueNode memSpace[QUEUESIZE];
} Queue;

queueNode* myMalloc(Queue* myQueue);
queueNode* newNode(Queue* myQueue, uint32_t data, queueNode* next);
Queue newQueue();
void enqueue(Queue* myQueue, uint32_t data);
uint32_t peek(Queue* myQueue);
uint32_t dequeue(Queue* myQueue);


#endif /* MRBUTIL_QUEUE_H_ */
