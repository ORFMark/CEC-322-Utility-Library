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
#include "driverlib/comp.h"
#include "grlib/grlib.h"
#include "utils/uartstdio.h"
#include "drivers/cfal96x64x16.h"
#include "drivers/buttons.h"
#include "mrbUtil/cec322peripherals.h"

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
* Function Name: UARTConsolePrint
* Purpose: Prints a given string to the console
* Inputs: The string to be printed
* Outputs: None
* Notes: Sends in improper string across the serial interface. Not safe to feed
*        other programs. Developed from UARTSend function from CJ Long
*/
void UARTPrint(const char* printable) {
  uint8_t *pui8Buffer = (uint8_t*) printable;
  while (*pui8Buffer != '\0') {
    UARTCharPut(UART0_BASE, *pui8Buffer++);
  }
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
* Function Name: clearDisplay
* Purpose: clears the OLED for writing
* Inputs: a pointer to a screem
* Outputs: none
* Notes: none
*/
void clearDisplay(tContext* sContext, bool preserveBanner) {
  tRectangle sRect;
  sRect.i16XMin = 0;
  if (preserveBanner)
    sRect.i16YMin = 9;
  else 
    sRect.i16YMin = 0;
  sRect.i16XMax = GrContextDpyWidthGet(sContext) - 1;
  sRect.i16YMax = GrContextDpyHeightGet(sContext)-1;
  GrContextForegroundSet(sContext, ClrBlack);
  GrRectFill(sContext, &sRect);
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

/*
* Function Name:configureADC
* Purpose: Configures the ADC to read data into the given channel and sequence 
           from the given pin
* Inputs: ADC base, Sequece, Channel, location
* Outputs: None
* Notes: Must be called before any ADC functions can be used. 
*/
void configureADC(uint32_t ADC_Base, uint32_t sequenceNum, uint32_t channel, uint32_t pin) {
  GPIOPinTypeADC(GPIO_PORTD_BASE, pin);
  ADCSequenceDisable(ADC_Base, sequenceNum);
  ADCSequenceConfigure(ADC_Base, sequenceNum, ADC_TRIGGER_PROCESSOR, 0);
  ADCSequenceStepConfigure(ADC_Base, sequenceNum, 0, channel | ADC_CTL_IE |
                           ADC_CTL_END);
  ADCSequenceEnable(ADC_Base, sequenceNum);
  ADCIntClear(ADC_Base, sequenceNum);
}
/*
* Function Name: getADCData
* Purpose: gets data from the given ADC and puts it in the given array
* Inputs: ADC, and the array to place the data in
* Outputs: None
* Notes: none
*/
void getADCData(uint32_t ADC_Base, uint32_t sequenceNum, uint32_t* squenceArray) {
  ADCProcessorTrigger(ADC_Base, sequenceNum);
  while(!ADCIntStatus(ADC_Base, sequenceNum, false))
  {
  };
  ADCIntClear(ADC_Base, sequenceNum);
  ADCSequenceDataGet(ADC_Base, sequenceNum, squenceArray);
}
/*
* Function Name: init comparator
* Purpose: initalize comparator 0 to read data on pin C7
* Inputs: none
* Outputs: none
* Notes: none 
*/
void initComparator() {
   // Turn on peripheral
    SysCtlPeripheralEnable(SYSCTL_PERIPH_COMP0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);

    // Wait for peripheral to be turn on
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_COMP0) ||
                !SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOC));

    // Configuring the internal reference for the comparator to 1.65V
    ComparatorRefSet(COMP_BASE, COMP_REF_1_65V);

    // Configuring comparator
    ComparatorConfigure(COMP_BASE, 0, COMP_TRIG_NONE | COMP_INT_BOTH |
                        COMP_ASRCP_REF | COMP_OUTPUT_NORMAL);

    // Assigning pin for comparitor
    GPIOPinTypeComparator(GPIO_PORTC_BASE, GPIO_PIN_7);
}

void ButtonsConfigure(){
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOM);
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOM))
  {
  }
  GPIODirModeSet(GPIO_PORTM_BASE, ALL_BUTTONS, GPIO_DIR_MODE_IN);
  GPIOPadConfigSet(GPIO_PORTM_BASE, ALL_BUTTONS,
                   GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
  GPIOIntTypeSet(GPIO_PORTM_BASE, ALL_BUTTONS, GPIO_FALLING_EDGE);
  GPIOIntEnable(GPIO_PORTM_BASE, ALL_BUTTONS);
  IntEnable(INT_GPIOM);
}

  