// =====================================================================================================================
//
//    File             :  waveshare_epd_example.ino
//    Tested on        :  Arduino-IDE (1.8.2 & 1.9.0 Beta31), Arduino Uno/Nano; Lolin Nodemcu v3
//    Version          :  0.2
//    Created by       :  Tadeusz Miszczyk (tadeusz.miszczyk[at]gmail.com)
//    Library & HowTo  :  https://github.com/tmseth/waveshare-epd-library
//    Last changes     :  20018-01-06
//
// =====================================================================================================================
#ifndef    WEPDL_H
#define    WEPDL_H

#include <Arduino.h>
#include <SoftwareSerial.h>

// Memory
#define    FLASH          0
#define    MICROSD        1

// Screen rotation
#define    HORIZONTAL     0
#define    VERTICAL       1

// Languages
#define    ENGLISH        0x1E
#define    CHINESE        0x1F

// Font sizes
#define    SIZE32         0x01
#define    SIZE48         0x02
#define    SIZE64         0x03

// Colors
#define    BLACK          0x00
#define    DARK           0x01
#define    LIGHT          0x02
#define    WHITE          0x03

//----------------------------------------------------------------------------------------------------------------------
class wepdl
{
    private :
            uint8_t             _wake_up,
                                _reset;

            unsigned char       _global_color,
                                _global_background_color,
                                _cmd_buff[512];

            const unsigned char _cmd_handshake[8] = { 0xA5, 0x00, 0x09, 0x00, 0xCC, 0x33, 0xC3, 0x3C },
                                _cmd_read_baud[8] = { 0xA5, 0x00, 0x09, 0x02, 0xCC, 0x33, 0xC3, 0x3C },
                                _cmd_stopmode[8]  = { 0xA5, 0x00, 0x09, 0x08, 0xCC, 0x33, 0xC3, 0x3C },
                                _cmd_update[8]    = { 0xA5, 0x00, 0x09, 0x0A, 0xCC, 0x33, 0xC3, 0x3C },
                                _cmd_load_font[8] = { 0xA5, 0x00, 0x09, 0x0E, 0xCC, 0x33, 0xC3, 0x3C },
                                _cmd_load_pic[8]  = { 0xA5, 0x00, 0x09, 0x0F, 0xCC, 0x33, 0xC3, 0x3C };

            void _putchars       ( const unsigned char * ptr, int n);
            unsigned char _verify( const void * ptr, int n);


    public :
            wepdl                ( uint8_t rx,
                                   uint8_t tx,
                                   uint8_t wake_up,
                                   uint8_t reset );

            SoftwareSerial        *SoftSerial;

            // ------------- D E V I C E -------------------------------------------------------------------------------------------
            void initialize      ( void );
            void goSleep         ( void );
            void handShake       ( void );
            void reset           ( void );
            void wakeUp          ( void );
            void readBaud        ( void );

            // ------------- S C R E E N -------------------------------------------------------------------------------------------
            void clearScreen     ( void );
            void rotateScreen    ( unsigned char mode );
            void updateScreen    ( void );

            // ------------- S E T -------------------------------------------------------------------------------------------------
            void setBaud         ( long baud );
            void setColor        ( unsigned char color,
                                   unsigned char background_color,
                                   bool global_color = true );

            void setFont         ( unsigned char font,
                                   unsigned char language = ENGLISH );

            void setMemory       ( unsigned char mode );

            // ------------- D I S P L A Y -----------------------------------------------------------------------------------------
            void displayBitmap   ( int x,
                                   int y,
                                   const void * p );

            void displayCharacter( int x,
                                   int y,
                                   unsigned char ch );

            void displayText     ( int x,
                                   int y,
                                   const void * p );

            // ------------- I M A G E S -------------------------------------------------------------------------------------------

            void Picture         ( void );

            // ------------- ? ? ? ? -----------------------------------------------------------------------------------------------
            void FontLoad        ( void );

            // ------------- D R A W -----------------------------------------------------------------------------------------------
            void drawPixel       ( int x,
                                   int y );

            void drawLine        ( int A_x,
                                   int A_y,
                                   int B_x,
                                   int B_y,
                                   int thickness = 1 );

            void drawCircle      ( int x,
                                   int y,
                                   int radius,
                                   bool fill = false );

            void drawRing        ( int x,
                                   int y,
                                   int radius,
                                   int border,
                                   unsigned char color,
                                   unsigned char background_color );

            void drawTriangle    ( int A_x,
                                   int A_y,
                                   int B_x,
                                   int B_y,
                                   int C_x,
                                   int C_y,
                                   bool fill = false );

            void drawRectangle   ( int A_x,
                                   int A_y,
                                   int C_x,
                                   int C_y,
                                   bool fill = false );

};
//----------------------------------------------------------------------------------------------------------------------
#endif




