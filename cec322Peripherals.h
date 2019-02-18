#ifndef __MRBUTIL_CEC322PERIPHERALS_H_
#define __MRBUTIL_CEC322PERIPHERALS_H_

void UARTConsolePrint(const char* printable, uint32_t size);
void initDisplay(tContext *sContext);
void configureUART();
void configureADC(uint32_t ADC, uint32_t sequenceNum, uint32_t channel, uint32_t pin);
void getADCData(uint32_t ADC_Base, uint32_t sequenceNum, uint32_t* squenceArray);

#endif /* CEC322PERIPHERALS_H_ */