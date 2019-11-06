// =====================================================================================================================
//
//    File             :  wepdl_display_bitmap.ino
//    Tested on        :  Arduino-IDE (1.8.2 & 1.9.0 Beta31), Arduino Uno/Nano; Lolin Nodemcu v3, Wemos D1 mini
//    Library Version  :  0.0.3
//    Created by       :  Tadeusz Miszczyk (tadeusz.miszczyk[at]gmail.com)
//    Library          :  https://github.com/8tm/wepdl
//    Wiki             :  https://github.com/8tm/wepdl/wiki
//    Last changes     :  2019-11-06

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
    EPD->rotateScreen  ( HORIZONTAL );                         // Set rotation to HORIZONTAL (HORIZONTAL / VERTICAL)
    EPD->clearScreen();                                        // Clear screen

    EPD->displayBitmap ( 0, 0, "PIC4.BMP" );                   // Display bitmap from FLASH ( max 10 uppercase chars in name, including ".BMP" )
                                                               // displayBitmap ( X_POSITION, Y_POSITION, "FILENA.BMP" )

    EPD->updateScreen();                                       // Update screen
    EPD->goSleep();                                            // Go to Sleep mode ( use wakeUp() before next work with display )
}
//----------------------------------------------------------------------------------------------------------------------
void loop(){}
//----------------------------------------------------------------------------------------------------------------------
