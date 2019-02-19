#ifndef __MRBUTIL_CEC322UTIL_H_
#define __MRBUTIL_CEC322UTIL_H_

//decesionBits: AIN-1-Mode | Blinky | Display Splash | Clear the screen | Print the menu| AIN-2-Mode | AIN-2-Mode | Quit


#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/fpu.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "driverlib/rom.h"
#include "driverlib/adc.h"
#include "grlib/grlib.h"
#include "drivers/cfal96x64x16.h"
#define ENABLE_BLINKY  0x80   
#define DISPLAY_SPLASH 0x40
#define SCREEN_CLEAR   0x20
#define PRINT_MENU     0x10
#define USER_TOGGLE_1  0x08
#define USER_TOGGLE_2  0x04
#define USER_TOGGLE_3  0x02
#define USER_TOGGLE_4  0x01
#define QUIT           0x00
#define START_STATE    0x80
#define BLINKY_LENGTH 20
#define SPLASH_LENGTH 1000

inline void delay(uint32_t milliseconds);
void blinky(void);
void initBlinky(void);
void printMenu(const char** userToggles, uint8_t* sizes, 
               const uint8_t numberOfPrompts);
void processMenuPolled(uint8_t *decisionBits);
void processMenuChar(uint8_t *decisionBits, uint8_t localChar);
void printSplashText(tContext* sContext);


#endif /* CEC322UTIL_H_ */