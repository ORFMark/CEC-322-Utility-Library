#ifndef __MRBUTIL_CEC322UTIL_H_
#define __MRBUTIL_CEC322UTIL_H_

//decesionBits: AIN-1-Mode | Blinky | Display Splash | Clear the screen | Print the menu| AIN-2-Mode | AIN-2-Mode | Quit

#define ENABLE_BLINKY  0x80
#define DISPLAY_SPLASH 0x40
#define SCREEN_CLEAR   0x20
#define PRINT_MENU     0x10
#define USER_TOGGLE_1  0x08
#define USER_TOGGLE_2  0x04
#define USER_TOGGLE_3  0x02
#define USER_TOGGLE_4  0x01
#define QUIT           0x00
#define START_STATE    0xD0

inline void delay(uint32_t milliseconds);
void blinky(void);
void initBlinky(void);
void printMenu(const char* userToggles, uint8_t* sizes, 
               const uint8_t numberOfPrompts);
void processMenuPolled(uint8_t *decisionBits);
void printSplashText(tContext* sContext);


#endif /* CEC322UTIL_H_ */