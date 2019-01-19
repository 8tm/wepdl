// =====================================================================================================================
//
//    File             :  wepdl_ring.ino
//    Tested on        :  Arduino-IDE (1.8.2 & 1.9.0 Beta31), Arduino Uno/Nano; Lolin Nodemcu v3, Wemos D1 mini
//    Library Version  :  0.2
//    Created by       :  Tadeusz Miszczyk (tadeusz.miszczyk[at]gmail.com)
//    Library & HowTo  :  https://github.com/8tm/waveshare-epd-library
//    Last changes     :  2018-04-18
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
    EPD->initialize();                                    // Initialize comunication with device
    EPD->wakeUp();                                        // Wake up device
    EPD->reset();                                         // Reset device
    EPD->rotateScreen  ( VERTICAL );                      // Set rotation to VERTICAL ( HORIZONTAL / VERTICAL )
    EPD->clearScreen();                                   // Clear screen

    EPD->drawRing( 300, 400, 300, 20, LIGHT, WHITE );     // Draw ring with border = 15 px using predefined colors (X, Y, R, BORDER, COLOR, BKCOLOR)
    EPD->drawRing( 300, 600,  50, 35, DARK,  WHITE );     // Draw ring with border = 35 px using predefined colors (X, Y, R, BORDER, COLOR, BKCOLOR)
    EPD->drawRing( 500, 400,  50, 15, DARK,  LIGHT );     // Draw ring with border = 15 px using predefined colors (X, Y, R, BORDER, COLOR, BKCOLOR)

    EPD->updateScreen();                                  // Update screen
    EPD->goSleep();                                       // Go to Sleep mode ( use wakeUp() before next work with display )
}
//----------------------------------------------------------------------------------------------------------------------
void loop(){}
//----------------------------------------------------------------------------------------------------------------------
