/*
 * queue.h
 *
 *  Created on: Feb 19, 2019
 *      Author: Mark
 */

#ifndef QUEUE_H_
#define QUEUE_H_


typedef struct node{
	struct node* next;
	char data;
} queueNode;

typedef struct{
	queueNode* head;
	queueNode* tail;
} Queue;

queueNode* newNode(char data, queueNode* next);
Queue newQueue();
void enqueue(Queue* myQueue, char data);
char peek(Queue* myQueue);
char dequeue(Queue* myQueue);

#endif /* QUEUE_H_ */
