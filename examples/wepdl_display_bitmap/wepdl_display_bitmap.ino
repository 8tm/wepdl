// =====================================================================================================================
//
//    File             :  waveshare_epd_example.ino
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

    EPD->displayBitmap ( 0, 0, "PIC4.BMP" );                   // Display bitmap from FLASH ( max 10 uppercase chars in name, including ".BMP" )

    EPD->updateScreen();                                       // Update screen
    EPD->goSleep();                                            // Go to Sleep mode ( use wakeUp() before next work with display )
}
//---------------------------------------------------------------------------------------------------------------------- 
void loop(){}
//---------------------------------------------------------------------------------------------------------------------- 
