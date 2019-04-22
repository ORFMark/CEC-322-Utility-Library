/*
 * File: queue.h
 * Project: Header Library  development for CEC320
 * Author: Mark Burrell
 * Version: 1.0 Tuesday February 19, 2019
 * Copywrite (c) 2019 Mark Burrell, all rights reserved
 * Repository: https://github.com/ORFMark/CEC-322-Utility-Library
 */

#ifndef MRBUTIL_BUFFER_H_
#define MRBUTIL_BUFFER_H_
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

#define MAX_BUF_SZ 16

typedef struct buf {
  float fbuf[MAX_BUF_SZ];
  uint16_t currentIndex;
  uint16_t valuesInBuffer;
} CircularBuffer;

void addValueToBuffer(CircularBuffer* buf, float valueToAdd);
float averageBuffer(CircularBuffer* buf);
CircularBuffer newBuffer();


#endif /* MRBUTIL_QUEUE_H_ */
