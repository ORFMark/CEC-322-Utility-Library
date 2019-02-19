/*
 * File: queue.h
 * Project: Header Library  development for CEC320
 * Author: Mark Burrell
 * Version: 1.0 Tuesday February 19, 2019
 * Copywrite (c) 2019 Mark Burrell, all rights reserved
 * Repository: https://github.com/ORFMark/CEC-322-Utility-Library
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
