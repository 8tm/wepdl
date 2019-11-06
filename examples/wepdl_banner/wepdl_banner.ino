// =====================================================================================================================
//
//    File             :  wepdl_banner.ino
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
String TITLE   = "wepdl",
       RELEASE = "Release : 2019-10-31  [ version 0.3 ]";
//----------------------------------------------------------------------------------------------------------------------
void setup()
{
    EPD->initialize();                                         // Initialize comunication with device
    EPD->wakeUp();                                             // Wake up device
    EPD->reset();                                              // Reset device
    EPD->setMemory     ( MICROSD );                            // Set memory to MICROSD    (    MICROSD / FLASH )
    EPD->rotateScreen  ( VERTICAL );                           // Set rotation to VERTICAL ( HORIZONTAL / VERTICAL )
    EPD->clearScreen();                                        // Clear screen

    wepdlScreen();                                             // Draw wepdl screen

    EPD->updateScreen();                                       // Update screen
    EPD->goSleep();                                            // Go to Sleep mode ( use wakeUp() before next work with display )
}
//----------------------------------------------------------------------------------------------------------------------
void loop(){}
//----------------------------------------------------------------------------------------------------------------------
void wepdlScreen()
{
    background();                                              // Draw own background

    for ( int i = 70; i <= 750; i = i+50 )                     // Simple lines effect
        EPD->drawLine( 0, i - 15, 600, i + 15, 2 );            // Draw line with thickness = 2

    EPD->setColor     ( BLACK, WHITE );                        // Set global color and background color (WHITE/LIGHT/DARK/BLACK)
    EPD->drawRing     ( 300, 400, 300, 15, LIGHT, WHITE );     // Draw main ring on lines effect

    EPD->setColor     ( BLACK, WHITE );                        // Set global color and background color (WHITE/LIGHT/DARK/BLACK)
    EPD->drawCircle   ( 100, 400, 50, true );                  // Draw filled circle (using global colors)     (X, Y, R, FILL (true/false) )
    EPD->drawCircle   ( 300, 200, 50 );                        // Draw empty circle  (using global colors)
    EPD->drawCircle   ( 310, 210, 50 );                        // Draw empty circle  (using global colors)

    EPD->drawRing     ( 300, 600, 50, 35, DARK,  WHITE );      // Draw ring with border = 35 px using predefined colors (X, Y, R, BORDER, COLOR, BKCOLOR)
    EPD->drawRing     ( 500, 400, 50, 15, LIGHT, WHITE );      // Draw ring with border = 15 px using predefined colors (X, Y, R, BORDER, COLOR, BKCOLOR)

    EPD->setColor     ( BLACK, LIGHT );                        // Set global color and background color (WHITE/LIGHT/DARK/BLACK)
    EPD->drawRectangle( 150, 200, 200, 300 );                  // Draw empty rectangle                         ( X1, Y1, X2, Y2 )
    EPD->drawRectangle( 160, 210, 210, 310 );                  // Draw empty rectangle + 10px (left + top)     ( X1, Y1, X2, Y2 )

    EPD->drawRectangle( 430, 470, 480, 570, true );            // Draw filled rectangle                        ( X1, Y1, X2, Y2, FILL (true/false) )

    EPD->drawTriangle ( 120, 570, 170, 470, 220, 570, true );  // Draw filled triangle                         ( X1, Y1, X2, Y2, X3, Y3 )
    EPD->drawTriangle ( 400, 300, 450, 200, 500, 300 );        // Draw empty triangle                          ( X1, Y1, X2, Y2, X3, Y3, FILL (true/false) )
    EPD->drawTriangle ( 410, 310, 460, 210, 510, 310 );        // Draw empty triangle                          ( X1, Y1, X2, Y2, X3, Y3, FILL (true/false) )

    EPD->drawLine     (  20, 130,  70, 180, 50 );
    EPD->drawLine     ( 480, 130, 530, 180, 50 );

    snowman();                                                 // Draw snowman
}
//----------------------------------------------------------------------------------------------------------------------
void background()
{
    EPD->setColor     ( DARK, WHITE );                         // Set global color and background color ( WHITE / LIGHT / DARK / BLACK)
    EPD->drawRectangle( 0,   0, 600, 50, true );               // Draw filled rectangle (upper  "title" bar)
    EPD->drawRectangle( 0, 750, 600, 800, true );              // Draw filled rectangle (bottom "release info" bar)

    EPD->setColor     ( BLACK, WHITE );                        // Set global color and background color ( WHITE / LIGHT / DARK / BLACK)
    EPD->drawLine     ( 0, 51, 600, 51, 2 );                   // Draw black line after upper bar with thickness = 2

    EPD->setColor     ( WHITE, DARK );                         // Set global color and background color ( WHITE / LIGHT / DARK / BLACK)
    EPD->setFont      ( SIZE32, ENGLISH );                     // Change font size to 32 English ( FONT_SIZE, LANGUAGE )( SIZE32 / SIZE48 / SIZE64 )
    EPD->setFont      ( SIZE32 );                              // Or just change size of font (English is a default language)
    EPD->displayText  ( 260,  9, TITLE.c_str() );              // Display library name in upper bar ( Text, X, Y )
    EPD->displayText  ( 80, 759, RELEASE.c_str() );            // Display info in bottom bar ( Text, X, Y )

    EPD->setColor     ( BLACK, WHITE );                        // Set global color and background color ( WHITE / LIGHT / DARK / BLACK)
    EPD->drawLine     ( 0, 748, 600, 748, 2 );                 // Draw black lines before bottom bar with thickness = 2
}
//----------------------------------------------------------------------------------------------------------------------
void snowman()
{
    int snX = 280,
        snY = 190;

    for ( int i = 8; i <= 18; i++ )
    {
       EPD->drawRing ( ( snX + 20 ), ( 770 - snY - ( i * 15 ) ), ( 100 - ( 3 * i ) ), 4, DARK, LIGHT );
       i += 4;
    }
    EPD->drawRing ( snX +  20, 570 - snY,  8, 2, BLACK, LIGHT );
    EPD->drawRing ( snX +  20, 600 - snY,  8, 2, BLACK, LIGHT );
    EPD->drawRing ( snX +  20, 655 - snY,  8, 2, BLACK, LIGHT );
    EPD->drawRing ( snX +  20, 685 - snY,  8, 2, BLACK, LIGHT );

    EPD->drawRing ( snX      , 500 - snY, 12, 3, DARK,  WHITE );
    EPD->drawRing ( snX +  40, 500 - snY, 12, 3, DARK,  WHITE );
    EPD->drawRing ( snX      , 500 - snY,  5, 2, BLACK, LIGHT );
    EPD->drawRing ( snX +  40, 500 - snY,  5, 2, BLACK, LIGHT );

    EPD->drawRing ( snX      , 524 - snY,  5, 1, DARK,  DARK );
    EPD->drawRing ( snX +  10, 528 - snY,  5, 1, DARK,  DARK );
    EPD->drawRing ( snX +  20, 530 - snY,  5, 1, DARK,  DARK );
    EPD->drawRing ( snX +  30, 528 - snY,  5, 1, DARK,  DARK );
    EPD->drawRing ( snX +  40, 524 - snY,  5, 1, DARK,  DARK );

    EPD->drawLine ( snX - 70, 500 - snY,
                    snX - 20, 550 - snY, 5 );   // Left "arm"

    EPD->drawLine ( snX +  60, 550 - snY,
                    snX + 110, 500 - snY, 5 );  // Right "arm"
}
//----------------------------------------------------------------------------------------------------------------------
