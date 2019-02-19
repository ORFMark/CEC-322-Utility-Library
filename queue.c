/*
 * queue.c
 *
 *  Created on: Feb 19, 2019
 *      Author: Mark
 */

#include <stdlib.h>
#include "queue.h"

queueNode* newNode(char data, queueNode* next) {
	queueNode* temp = (queueNode*) malloc(sizeof(queueNode));
	temp->next = next;
	temp->data = data;
	return temp;
}
Queue newQueue() {
	Queue newQueue;
	newQueue.head = NULL;
	newQueue.tail = NULL;
	return newQueue;
}
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

char peek(Queue* myQueue) {
    return myQueue->head->data;
}

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
