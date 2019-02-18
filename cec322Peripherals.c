#include <stdint.h>
#include <stdbool.h>
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

/*
* Function Name: UARTConsolePrint
* Purpose: Prints a given string to the console
* Inputs: The string to be printed and it's length. 
* Outputs: None
* Notes: Sends proper C strings to the UART in case they are being fed to 
*       another program
*/
void UARTConsolePrint(const char* printable, uint32_t size) {
  uint8_t *pui8Buffer; 
  pui8Buffer = (uint8_t*) printable;
  while(size-- && (*pui8Buffer) != '\0')
  {
    UARTCharPut(UART0_BASE, *pui8Buffer++);
  }
  UARTCharPut(UART0_BASE, '\0');
}

/*
* Function Name: initDisplay
* Purpose: initializes the OLED display
* Inputs: a pointer to a screem
* Outputs: none
* Notes: none
*/
void initDisplay(tContext *sContext) {

  // Initialize the display driver.
  CFAL96x64x16Init(); 
  
  // Initialize the graphics context and find the middle X coordinate.
  GrContextInit(sContext, &g_sCFAL96x64x16); 
}

/*
* Function Name:configureUART
* Purpose: configures the UART at 115200 Baud
* Inputs: None
* Outputs: None
* Notes: Must be called before any UART functions can be used. 
*/
void configureUART() {
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
  GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
  
  UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
                      (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                       UART_CONFIG_PAR_NONE));
}

void configureADC(uint32_t ADC_Base, uint32_t sequenceNum, uint32_t channel, uint32_t pin) {
  GPIOPinTypeADC(GPIO_PORTD_BASE, pin);
  ADCSequenceDisable(ADC_Base, sequenceNum);
  ADCSequenceConfigure(ADC_Base, sequenceNum, ADC_TRIGGER_PROCESSOR, 0);
  ADCSequenceStepConfigure(ADC_Base, sequenceNum, 0, channel | ADC_CTL_IE |
                           ADC_CTL_END);
  ADCSequenceEnable(ADC_Base, sequenceNum);
  ADCIntClear(ADC_Base, sequenceNum);
}

void getADCData(uint32_t ADC_Base, uint32_t sequenceNum, uint32_t* squenceArray) {
	ADCProcessorTrigger(ADC_Base, sequenceNum);
  while(!ADCIntStatus(ADC_Base, sequenceNum, false))
  {
  };
  ADCIntClear(ADC_Base, sequenceNum);
  ADCSequenceDataGet(ADC_Base, sequenceNum, squenceArray);
}