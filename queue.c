/*
 * File: queue.c
 * Project: Header Library development for CEC320
 * Author: Mark Burrell
 * Version: 1.0 Tuesday February 19, 2019
 * Copywrite (c) 2019 Mark Burrell, all rights reserved
 * Repository: https://github.com/ORFMark/CEC-322-Utility-Library
 */

#include <stdlib.h>
#include "queue.h"

/*
 * Function Name: newNode
 * Purpose: creates a new node for the queue.
 * Inputs: a character data and the pointer to the next node
 * Outputs: a proper queue node
 * Notes: never meant to be called by a forward-facing function
 */
queueNode* newNode(char data, queueNode* next) {
	queueNode* temp = (queueNode*) malloc(sizeof(queueNode));
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
	newQueue.head = NULL;
	newQueue.tail = NULL;
	return newQueue;
}

/*
 * Function Name: enqueue
 * Purpose: adds a key to the queue
 * Inputs: a pointer to the queue and the data to be added
 * Outputs: None
 * Notes: N/A
 */
void enqueue(Queue* myQueue, char data) {
	queueNode* nodeToAdd= newNode(data, NULL);
	if(myQueue->tail != NULL) {
		myQueue->tail->next = nodeToAdd;
		myQueue->tail = nodeToAdd;
		if(myQueue->head == NULL) {
			myQueue->head = nodeToAdd;
		}
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
char peek(Queue* myQueue) {
	if(myQueue->head != NULL) {
		return myQueue->head->data;
	}
	else {
		return '\0';
	}
}

/*
 * Function Name: dequeue
 * Purpose: moves the list down and returns the first value in the queue
 * Inputs: a pointer to the queue
 * Outputs: The first value in the queue
 * Notes: N/A
 */
char dequeue(Queue* myQueue) {
	char data = '\0';
	if(myQueue->head != NULL) {
		data = myQueue->head->data;
		myQueue->head = myQueue->head->next;
		if(myQueue->head == NULL) {
			myQueue->tail = NULL;
		}
	}
	return data;
}
