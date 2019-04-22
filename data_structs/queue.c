/*
* File: queue.c
* Project: Header Library development for CEC320
* Author: Mark Burrell
* Version: 1.0 Tuesday February 19, 2019
* Copywrite (c) 2019 Mark Burrell, all rights reserved
* Repository: https://github.com/ORFMark/CEC-322-Utility-Library
*/

#include<stdlib.h>
#include "queue.h"

/*
* Function Name: myMalloc
* Purpose: determines where to put a newly created node
* Inputs: a pointer for queue whose memory space is in use
* Outputs: aa pointer a node location
* Notes: never meant to be called by a forward-facing function
*/
queueNode* myMalloc(Queue* myQueue) {
  if(myQueue->allocatedNodes < QUEUESIZE) {
    
    queueNode* node = &(myQueue->memSpace[myQueue->allocatedNodes]);
    myQueue->allocatedNodes = (myQueue->allocatedNodes + 1) % QUEUESIZE;
    return node;
  }
  else {
    return 0;
  }
}

/*
* Function Name: newNode
* Purpose: creates a new node for the queue.
* Inputs: a uint8_tacter data and the pointer to the next node
* Outputs: a proper queue node
* Notes: never meant to be called by a forward-facing function
*/
queueNode* newNode(Queue* myQueue, uint32_t data, queueNode* next) {
  queueNode* temp = myMalloc(myQueue);
  temp->next = next;
  temp->data = data;
  return temp;
}

/*
* Function Name: newQueue
* Purpose: creates a new queue
* Inputs: None
* Outputs: a empty queue.
* Notes: N/A
*/
Queue newQueue() {
  
  Queue newQueue;
  newQueue.head = 0;
  newQueue.tail = 0;
  newQueue.allocatedNodes = 0;
  return newQueue;
}

/*
* Function Name: enqueue
* Purpose: adds a key to the queue
* Inputs: a pointer to the queue and the data to be added
* Outputs: None
* Notes: N/A
*/
void enqueue(Queue* myQueue, uint32_t data) {
  queueNode* nodeToAdd= newNode(myQueue, data, 0);
  if(myQueue->tail != 0) {
    myQueue->tail->next = nodeToAdd;
    myQueue->tail = nodeToAdd;
  }
  else {
    myQueue->head = nodeToAdd;
    myQueue->tail = nodeToAdd;
  }
}

/*
* Function Name: peek
* Purpose: checks the head value without dequeueing it
* Inputs: a pointer to the queue
* Outputs: The first value in the queue
* Notes: N/A
*/
uint32_t peek(Queue* myQueue) {
  if(myQueue->head != 0) {
    return myQueue->head->data;
  }
  else {
    return -1;
  }
}

/*
* Function Name: dequeue
* Purpose: moves the list down and returns the first value in the queue
* Inputs: a pointer to the queue
* Outputs: The first value in the queue
* Notes: N/A
*/
uint32_t dequeue(Queue* myQueue) {
  uint32_t data = '\0';
  if(myQueue->head != 0 && myQueue->allocatedNodes != 0) {
    myQueue->lastProcessed  = myQueue->head->data;
    data = myQueue->lastProcessed;
    myQueue->head = myQueue->head->next;
    if(myQueue->head == 0) {
      myQueue->tail = 0;
    }
  }
  return data;
}
