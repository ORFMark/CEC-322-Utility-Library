#ifndef _MRBUTIL_I2CWRITE_H_
#define _MRBUTIL_I2CWRITE_H_

#include <stdint.h>
#include <stdbool.h>
#include <limits.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/sysctl.h"
#include "driverlib/i2c.h"

static unsigned long ResetI2C(uint32_t i2c_base);
static unsigned long WaitI2CDone(unsigned int long ulBase);
int i2c_write(uint32_t i2c_base_addr, 
              unsigned char dev_addr, 
              unsigned num_char, 
              unsigned char *write_buf);
#endif /*_MRBUTIL_I2CWRITE_H_*/