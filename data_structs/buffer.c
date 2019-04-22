#include "buffer.h"
/*
* Function Name: addValueToBuffer
* Purpose: adds a floating point value to the buffer. 
* Inputs: Pointer to the buffer and the value to be added
* Outputs: None
* Notes: Will overwrite exisitng data if it is full rather then preventing
*        more values from being added. 
*/
void addValueToBuffer(CircularBuffer* buf, float valueToAdd) {
  buf->fbuf[buf->currentIndex] = valueToAdd;
  buf->currentIndex = (buf->currentIndex+1) % MAX_BUF_SZ;
  if(buf->valuesInBuffer < MAX_BUF_SZ) {
    buf->valuesInBuffer++;
  }
}

/*
* Function Name: averageBuffer
* Purpose: computes an unweighed avererage across the values in the buffer 
* Inputs: Pointer to the buffer to be averaged
* Outputs: the unweighted average of the buffer
* Notes: Will eventually be transitioned to a weighted average to give recent
*       Inputs more weight
*/
float averageBuffer(CircularBuffer* buf) {
  float average;
  uint16_t i = 0;
  for(i = 0; i < buf->valuesInBuffer; i++) {
    average += buf->fbuf[i];
  }
  return average/buf->valuesInBuffer;
}
/*
* Function Name: newBuffer
* Purpose: creates and configures a new circular buffer
* Inputs: None
* Outputs: a new buffer with proper values
* Notes: depends on the MAX_BUF_SZ define to avoid writing over the end
*/
CircularBuffer newBuffer() {
  CircularBuffer newBuff;
  newBuff.currentIndex = 0;
  newBuff.valuesInBuffer = 0;
  return newBuff;
}
