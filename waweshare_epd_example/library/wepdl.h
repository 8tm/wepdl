// =====================================================================================================================
//
//    File             : wepdl.h
//    Environment      : Arduino Uno/Nano; Lolin Nodemcu v3
//    Version          : V1.0
//    Created by       : Tadeusz Miszczyk (tadeusz.miszczyk[at]gmail.com)
//
// =====================================================================================================================
#ifndef    WEPDL_H
#define    WEPDL_H

#include <Arduino.h>
#include <SoftwareSerial.h>

#define    FLASH          0
#define    MICROSD        1

#define    HORIZONTAL     0
#define    VERTICAL       1

#define    ENGLISH        0x1E
#define    CHINESE        0x1F
#define    SIZE32         0x01
#define    SIZE48         0x02
#define    SIZE64         0x03

#define    WHITE          0x03
#define    LIGHT          0x02
#define    DARK           0x01
#define    BLACK          0x00

//----------------------------------------------------------------------------------------------------------------------

class wepdl
{

    private :
            uint8_t _wakeup;
            uint8_t _reset;
            unsigned char _global_color;
            unsigned char _global_background_color;
            unsigned char _cmd_buff[512];
            const unsigned char _cmd_handshake[8] = {0xA5, 0x00, 0x09, 0x00, 0xCC, 0x33, 0xC3, 0x3C};
            const unsigned char _cmd_read_baud[8] = {0xA5, 0x00, 0x09, 0x02, 0xCC, 0x33, 0xC3, 0x3C};
            const unsigned char _cmd_stopmode[8]  = {0xA5, 0x00, 0x09, 0x08, 0xCC, 0x33, 0xC3, 0x3C};
            const unsigned char _cmd_update[8]    = {0xA5, 0x00, 0x09, 0x0A, 0xCC, 0x33, 0xC3, 0x3C};
            const unsigned char _cmd_load_font[8] = {0xA5, 0x00, 0x09, 0x0E, 0xCC, 0x33, 0xC3, 0x3C};
            const unsigned char _cmd_load_pic[8]  = {0xA5, 0x00, 0x09, 0x0F, 0xCC, 0x33, 0xC3, 0x3C};
            void _putchars(const unsigned char * ptr, int n);
            unsigned char _verify(const void * ptr, int n);
            
    public :
            wepdl            ( uint8_t rx, uint8_t tx, uint8_t wakeup, uint8_t reset );
            SoftwareSerial    *SoftSerial;

            // ------------- S E T -------------------------------------------------------------------------------------------------
            void Color       ( unsigned char color, unsigned char bkcolor, bool global_color = true );
            void Font        ( unsigned char Font, unsigned char Language = ENGLISH );

            // ------------- S C R E E N -------------------------------------------------------------------------------------------
            void Clear_Screen    ( void );
            void Rotate_Screen   ( unsigned char mode );
            void Update_Screen   ( void );

            // ------------- T E X T -----------------------------------------------------------------------------------------------
            void Character   ( unsigned char ch, int x0, int y0 );
            void Text        ( const void * p, int x0, int y0 );

            // ------------- I M A G E S -------------------------------------------------------------------------------------------
            void Bitmap      ( const void * p, int x0, int y0 );
            void Picture     ( void );

            // ------------- ? ? ? ? -----------------------------------------------------------------------------------------------
            void Font_load   ( void );

            // ------------- D E V I C E -------------------------------------------------------------------------------------------
            void HandShake   ( void );
            void Initialize  ( void );
            void Memory      ( unsigned char mode );
            void Reset       ( void );
            void Go_Sleep    ( void );
            void Wake_Up     ( void );
            void SetBaud     ( long baud );
            void ReadBaud    ( void );

            // ------------- D R A W -----------------------------------------------------------------------------------------------
            void drawCircle      ( int x0, int y0, int r, bool fill = false );
            void drawRing        ( int x0, int y0, int r, int border, unsigned char color, unsigned char bkcolor);
            void drawLine        ( int X, int Y, int X1, int Y1 );
            void drawPixel       ( int X, int Y );
            void drawRectangle   ( int x0, int y0, int x1, int y1, bool fill = false );
            void drawTriangle    ( int x0, int y0, int x1, int y1, int x2, int y2, bool fill = false );
};
//---------------------------------------------------------------------------------------------------------------------- 
#endif
