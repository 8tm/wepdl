#include "wepdl.h"
#include <SoftwareSerial.h>
//---------------------------------------------------------------------------------------------------------------------- 
//         PIN     Nodemcu v3 (lolin) | Arduino UNO | 
//---------------------------------------------------------------------------------------------------------------------- 
#define    RX      D7 // ( GPIO13 )   |    10       | 
#define    TX      D8 // ( GPIO15 )   |    11       | 
#define    WAKEUP  D6 // ( GPIO12 )   |     2       | 
#define    RESET   D5 // ( GPIO14 )   |     3       | 
//---------------------------------------------------------------------------------------------------------------------- 
String TITLE   = "wepdl",
       RELEASE = "Release : 2018-01-05  [ version 1.0 ]";
       

wepdl * EPD = new wepdl( RX, TX, WAKEUP, RESET );

//---------------------------------------------------------------------------------------------------------------------- 
void background_template()
{
    EPD->Color( DARK, WHITE );
    EPD->drawRectangle( 0,   0, 600, 50, true );
    EPD->drawRectangle( 0, 750, 600, 800, true );
    
    EPD->Color( BLACK, WHITE );
    EPD->drawLine( 0, 51, 600, 51 );
    EPD->drawLine( 0, 52, 600, 52 );
    
    EPD->Color( WHITE, DARK );
    EPD->Font( SIZE32 );                                      // Font Size ( SIZE32 / SIZE48 / SIZE64 )
    EPD->Text( TITLE.c_str(), 260, 9 );                      // Draw String / ( Text, X, Y )
    
    EPD->Font( SIZE32 );
    EPD->Text( RELEASE.c_str(), 80, 759 );
    
    EPD->Color( BLACK, WHITE );
    EPD->drawLine( 0, 748, 600, 748 );
    EPD->drawLine( 0, 749, 600, 749 );
}
//---------------------------------------------------------------------------------------------------------------------- 
void wepdlLogo()
{
    for (int i = 70; i <= 750; i = i+50)
        EPD->drawLine(0,i-15,600,i+15);
    
    EPD->Color( BLACK, WHITE );                               // Set global color and background color ( WHITE / LIGHT / DARK / BLACK)
    EPD->drawRing  ( 300, 400, 300, 15, LIGHT, WHITE );

    EPD->Color( BLACK, WHITE );                               // Set global color and background color ( WHITE / LIGHT / DARK / BLACK)
    EPD->drawCircle( 100, 400,  50, true );                   // Draw filled circle (using global colors) (X, Y, R, FILL (true/false) )
    EPD->drawCircle( 300, 200, 50 );                          // Draw empty circle  (using global colors) 

    EPD->drawRing( 300, 600, 50, 35, DARK, WHITE );           // Draw ring with border = 35 px using predefined colors (X, Y, R, BORDER, COLOR, BKCOLOR)
    EPD->drawRing( 500, 400, 50, 15, LIGHT, WHITE );          // Draw ring with border = 15 px using predefined colors (X, Y, R, BORDER, COLOR, BKCOLOR)
    
    EPD->Color( BLACK, LIGHT );
    EPD->drawRectangle( 150, 200, 200, 300 );                 // Draw empty rectangle                         ( X1, Y1, X2, Y2 )
    EPD->drawRectangle( 160, 210, 210, 310 );                 // Draw empty rectangle + 10px (left + top)     ( X1, Y1, X2, Y2 )
    
    EPD->drawRectangle( 430, 470, 480, 570, true );           // Draw filled rectangle                        ( X1, Y1, X2, Y2, FILL (true/false) )
    
    EPD->drawTriangle( 120, 570, 170, 470, 220, 570 );        // Draw filled triangle                         ( X1, Y1, X2, Y2, X3, Y3 )
    EPD->drawTriangle( 400, 300, 450, 200, 500, 300, true );  // Draw empty triangle                          ( X1, Y1, X2, Y2, X3, Y3, FILL (true/false) )

    snowman();                                                // Draw snowman    
}
//---------------------------------------------------------------------------------------------------------------------- 
void snowman()
{
    int snX = 280,
        snY = 190;
    
    for ( int i = 8; i <= 18; i++ )
    {
       EPD->drawRing( ( snX + 20 ), ( 770 - snY - ( i * 15 ) ), ( 100 - ( 3 * i ) ), 4, DARK, LIGHT);
       i += 4;
    }
    EPD->drawRing( snX +  20, 570 - snY,  8, 2, BLACK, LIGHT );
    EPD->drawRing( snX +  20, 600 - snY,  8, 2, BLACK, LIGHT );
    EPD->drawRing( snX +  20, 655 - snY,  8, 2, BLACK, LIGHT );
    EPD->drawRing( snX +  20, 685 - snY,  8, 2, BLACK, LIGHT );

    EPD->drawRing( snX      , 500 - snY, 12, 3, DARK,  WHITE );
    EPD->drawRing( snX +  40, 500 - snY, 12, 3, DARK,  WHITE );
    EPD->drawRing( snX      , 500 - snY,  5, 2, BLACK, LIGHT );
    EPD->drawRing( snX +  40, 500 - snY,  5, 2, BLACK, LIGHT );
 
    EPD->drawRing( snX      , 524 - snY,  5, 1, DARK,  DARK );
    EPD->drawRing( snX +  10, 528 - snY,  5, 1, DARK,  DARK );
    EPD->drawRing( snX +  20, 530 - snY,  5, 1, DARK,  DARK );
    EPD->drawRing( snX +  30, 528 - snY,  5, 1, DARK,  DARK );
    EPD->drawRing( snX +  40, 524 - snY,  5, 1, DARK,  DARK );  
}
//---------------------------------------------------------------------------------------------------------------------- 
void setup()
{
    EPD->Initialize();
    EPD->Wake_Up();
    EPD->Reset();
    EPD->Memory(MICROSD);                                     // Set memory to MICROSD (MICROSD / FLASH)
    EPD->Rotate_Screen(VERTICAL);                             // Set rotation to VERTICAL (HORIZONTAL / VERTICAL)

    EPD->Clear_Screen();                                      // Clear screen

    background_template();                                    // Draw background
    wepdlLogo();
    
    EPD->Update_Screen();
    EPD->Go_Sleep();
}
//---------------------------------------------------------------------------------------------------------------------- 
void loop()
{
}
//---------------------------------------------------------------------------------------------------------------------- 
