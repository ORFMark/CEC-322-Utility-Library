#include <stdint.h>
#include <stdbool.h>
#include <math.h> 
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/rom.h"
#include "driverlib/adc.h"
#include "grlib/grlib.h"
#include "utils/uartstdio.h"
#include "drivers/cfal96x64x16.h"
#include "drivers/buttons.h"
#include "mrbUtil/cec322Util.h"
#include "mrbUtil/cec322Peripherals.h"
#define BLINKY_DELAY 5
#define BLINKY_DELAY_90  90000

/*
* Function Name: delay
* Purpose: To delay the loop by an approximate amount of milliseconds
* Inputs: uint32_t for the number of milliseconds
* Outputs: None
* Notes: Only approximate, will be thrown off by ISRs
*/
void delay(uint32_t milliseconds) {
 //Uses the ROM version to increae accuracy. Each loop cycle takes three CPU
 //Cycles to execute. 
 ROM_SysCtlDelay((SysCtlClockGet() * milliseconds )/3000); 
}

/*
* Function Name: blinky
* Purpose: To run the heartbeat blinky 
* Inputs: none
* Outputs: none
* Notes: Can be starved, Must call initblinky before use
*/
void blinky(void) {
  static uint32_t counter = 0;
  static bool enableLED = true;
  counter++;
   if(counter == BLINKY_DELAY) {
    enableLED = !enableLED;
    counter = 0;
   }
   enableLED == true ? GPIOPinWrite(GPIO_PORTG_BASE, GPIO_PIN_2, GPIO_PIN_2)
     : killBlinky();
    
  
}

/*
* Function Name: initBlinky
* Purpose: initilize the heartbeat LED. 
* Inputs: none
* Outputs: none
* Notes: none
*/
void initBlinky(void) {
  //Enable the GPIO port that is used for the on-board LED.
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG); 
  // Check if the peripheral access is enabled.
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOG)) {} 
  //Enable the GPIO Pin for the LED, set it to output, 
  //and enable the pin for digital Function
  GPIOPinTypeGPIOOutput(GPIO_PORTG_BASE, GPIO_PIN_2); 

}

/*
* Function Name: killBlinky
* Purpose: turn off the heartbeat LED.
* Inputs: none
* Outputs: none
* Notes: none
*/
void killBlinky(void) {
    GPIOPinWrite(GPIO_PORTG_BASE, GPIO_PIN_2, 0);
}


/*
* Function Name: printMenu
* Purpose: prints the Menu to the UART
* Inputs: array of strings, an array of their lengths, and the array lengths
* Outputs: none
* Notes: Contains 3 slots for user-driven input. 
*/
void printMenu(const char** userToggles, uint8_t* sizes, 
               const uint8_t numberOfPrompts) {
  uint8_t counter = 0;
  char* printables[4][32];
  
  if (numberOfPrompts > 0) {
    for(counter = 0; counter < numberOfPrompts; counter++) {
      sprintf(printables[counter], "%d: %s", counter+1, (char*)userToggles[counter]);
    }
  }
  
  UARTConsolePrint("Enter the letter to preform the desired function.\n\r", 51
                   );
  UARTConsolePrint("b: toggle blinky operation\n\r", 29);
  UARTConsolePrint("s: Print the Splash\n\r", 22);
  UARTConsolePrint("m: print this menu\n\r", 22);
  UARTConsolePrint("c: clear the screen\n\r", 22);
  
  for(counter = 0; counter < numberOfPrompts; counter++) {
    UARTConsolePrint((char*)printables[counter], sizes[counter]+3);
    UARTConsolePrint("\n\r", 2);
  } 
  UARTConsolePrint("q: quit this program\n\r", 24);
}

/*
* Function Name: processMenuPolled
* Purpose: processing of the menu in a polled-driven manner
* Inputs:8 bit vector of toggles
* Outputs: none
* Notes: assumes polled operation. 
*/
void processMenuPolled(uint8_t *decisionBits) {
  int32_t local_char;
  while(UARTCharsAvail(UART0_BASE)) 
  {
    local_char = UARTCharGet(UART0_BASE);
    if(local_char != -1) {
      switch (local_char) {
      case 'b':
        *(decisionBits) ^= ENABLE_BLINKY;
        killBlinky();
        break;
       case 's':
        *(decisionBits) ^= DISPLAY_SPLASH;
        break;
        case 'c':
        *(decisionBits) ^= SCREEN_CLEAR;
        break;
        case 'm':
        *(decisionBits) ^= PRINT_MENU;
        break;
        case '1':
        *(decisionBits) ^= USER_TOGGLE_1;
        break;
        case '2':
        *(decisionBits) ^= USER_TOGGLE_2;
        break;
        case '3':
        *(decisionBits) ^= USER_TOGGLE_3;
        break;
        case 'q':
        *(decisionBits) = 0x00;
        break;
      default: {
        UARTConsolePrint("INVALID COMMAND", 16); 
      }
      }
    }
  }
  
}

/*
* Function Name: processMenuChar
* Purpose: processing of a single character through the menu options to control
           a 8bit toggle vector
* Inputs:8 bit vector of toggles
* Outputs: none
* Notes: none 
*/
void processMenuChar(uint8_t *decisionBits, uint32_t localChar) {
      switch (localChar) {
      case 'b':
        *(decisionBits) ^= ENABLE_BLINKY;
        killBlinky();
        break;
       case 's':
        *(decisionBits) ^= DISPLAY_SPLASH;
        break;
        case 'c':
        *(decisionBits) ^= SCREEN_CLEAR;
        break;
        case 'm':
        *(decisionBits) ^= PRINT_MENU;
        break;
        case '1':
        *(decisionBits) ^= USER_TOGGLE_1;
        break;
        case '2':
        *(decisionBits) ^= USER_TOGGLE_2;
        break;
        case '3':
        *(decisionBits) ^= USER_TOGGLE_3;
        break;
        case 'q':
        *(decisionBits) ^= QUIT;
        break;
      }
  
}

/*
* Function Name: printSplashText
* Purpose: prints out the splash screen. 
* Inputs: Screen Context
* Outputs: None
* Notes: After calling the inital state of the screen will need to be redrawn
*/
void printSplashText(tContext* sContext) {
  /*Begin OLED print*/
  GrContextForegroundSet(sContext, ClrWhite);
  GrContextFontSet(sContext, g_psFontCm12/*g_psFontFixed6x8*/);
  GrStringDraw(sContext, "MRB_DG_CEC322_Lab4_v1", -1,
               0,
               ((GrContextDpyHeightGet(sContext) - 24) / 2) + -12,
               1);
  GrFlush(sContext);
  delay(SPLASH_LENGTH);
  clearDisplay(sContext, false);
  /*end OLED*/
}

/*
* Function Name: floatToString
* Purpose: uses the IEEE FLoating point standard to convert a float to a str. 
* Inputs: a float
* Outputs: a string representation of the float
* Notes: Provided by B.T. Davis
*/

char *floatToString(float x)
{
  // Use of static allocation here BAD code style
  // Functional but quick & dirty use only
  static char buf[32];
  int mantissa = (int)(x);
  int fraction = abs((int)((x - mantissa)*1000));
  if (fraction > 99)
  {
    sprintf(buf, "%d.%d    ", mantissa, fraction);
  } 
  else if (fraction > 9)
  {
    sprintf(buf, "%d.0%d   ", mantissa, fraction);
  }
  else
  {    
    sprintf(buf, "%d.00%d  ", mantissa, fraction);
  }
  
  return buf;
}

