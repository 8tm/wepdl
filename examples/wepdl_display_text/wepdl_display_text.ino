// =====================================================================================================================
//
//    File             :  wepdl_display_text.ino
//    Tested on        :  Arduino-IDE (1.8.2 & 1.9.0 Beta31), Arduino Uno/Nano; Lolin Nodemcu v3, Wemos D1 mini
//    Library Version  :  0.2
//    Created by       :  Tadeusz Miszczyk (tadeusz.miszczyk[at]gmail.com)
//    Library & HowTo  :  https://github.com/tmseth/waveshare-epd-library
//    Last changes     :  20018-04-18
//
// =====================================================================================================================
#include "wepdl.h"
//---------------------------------------------------------------------------------------------------------------------- 
#define    RX      D7
#define    TX      D8
#define    WAKEUP  D6
#define    RESET   D5
//---------------------------------------------------------------------------------------------------------------------- 
wepdl * EPD = new wepdl( RX, TX, WAKEUP, RESET );
//---------------------------------------------------------------------------------------------------------------------- 
void setup()
{
    EPD->initialize();                                         // Initialize comunication with device
    EPD->wakeUp();                                             // Wake up device
    EPD->reset();                                              // Reset device
    EPD->setMemory     ( FLASH );                              // Set memory to FLASH (MICROSD / FLASH)
    EPD->rotateScreen  ( HORIZONTAL );                         // Set rotation to VERTICAL (HORIZONTAL / VERTICAL)
    EPD->clearScreen();                                        // Clear screen
    
    // ENGLISH FONT:
    EPD->setFont(SIZE32, ENGLISH);                     // Set font size = 32 and set (from now) English font 
    EPD->displayText(100, 100, "SIZE32: Hello, World!"); // Display text on X_POSITION=100 and Y_POSITION = 100
    
    EPD->setFont(SIZE48);                              // Set font size = 48 (font is still English)
    EPD->displayText(100, 150, "SIZE48: Hello, World!"); // Display text on X_POSITION=100 and Y_POSITION = 150
    
    EPD->setFont(SIZE64);                              // Set font size = 64 (font is still English)
    EPD->displayText(100, 210, "SIZE64: Hello, World!"); // Display text on X_POSITION=100 and Y_POSITION = 210

    // CHINESE FONT:
    // Chinese example text
    char buff[] = {'S', 'I', 'Z', 'E', 'X', 'X', ':', ' ', 0xc4, 0xe3, 0xba, 0xc3, 0xca, 0xc0, 0xbd, 0xe7, 0};

    buff[4] = '3';
    buff[5] = '2';
    EPD->setFont(SIZE32, CHINESE);           // Set font size = 32 and set (from now) Chinese font 
    EPD->displayText(100, 300, buff);        // Display buff text on X_POSITION=100 and Y_POSITION = 300

    buff[4] = '4';
    buff[5] = '8';
    EPD->setFont(SIZE48);                    // Set font size = 48 (font is still Chinese)
    EPD->displayText(100, 350, buff);        // Display buff text on X_POSITION=100 and Y_POSITION = 350

    buff[4] = '6';
    buff[5] = '4';
    EPD->setFont(SIZE64);                    // Set font size = 48 (font is still Chinese)
    EPD->displayText(100, 410, buff);        // Display buff text on X_POSITION=100 and Y_POSITION = 410

    EPD->updateScreen();                                       // Update screen
    EPD->goSleep();                                            // Go to Sleep mode ( use wakeUp() before next work with display )
}
//---------------------------------------------------------------------------------------------------------------------- 
void loop(){}
//---------------------------------------------------------------------------------------------------------------------- 
