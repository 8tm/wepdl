// =====================================================================================================================
//
//    File             :  wepdl.cpp
//    Tested on        :  Arduino-IDE (1.8.2 & 1.9.0 Beta31), Arduino Uno/Nano; Lolin Nodemcu v3
//    Version          :  0.2
//    Created by       :  Tadeusz Miszczyk (tadeusz.miszczyk[at]gmail.com)
//    Library & HowTo  :  https://github.com/8tm/waveshare-epd-library
//    Last changes     :  2018-01-06
//
// =====================================================================================================================
#include "wepdl.h"
//----------------------------------------------------------------------------------------------------------------------
extern "C" {
#include "user_interface.h"
}
//----------------------------------------------------------------------------------------------------------------------
wepdl :: wepdl ( uint8_t rx,
                 uint8_t tx,
                 uint8_t wake_up,
                 uint8_t reset )
{
    _wake_up   = wake_up;
    _reset     = reset;
    SoftSerial = new SoftwareSerial( rx, tx );
}
//----------------------------------------------------------------------------------------------------------------------
void wepdl::_putchars( const unsigned char * ptr,
                       int n )
{
    int i,
        x;

    for( i = 0; i < n; i++ )
    {
        x = ptr[i];
        SoftSerial->write( x );
    }
}
//----------------------------------------------------------------------------------------------------------------------
unsigned char wepdl::_verify( const void * ptr,
                              int n )
{
    int i;
    unsigned char * p = ( unsigned char * ) ptr;
    unsigned char result;
    for( i = 0, result = 0; i < n; i++ )
    {
        result ^= p[i];
    }
    return result;
}
//----------------------------------------------------------------------------------------------------------------------
void wepdl::initialize ( void )
{
    SoftSerial->begin( 115200 );

    pinMode( _wake_up, HIGH );

    pinMode( _reset, HIGH );
}
//----------------------------------------------------------------------------------------------------------------------
void wepdl::goSleep       ( void )
{
    memcpy( _cmd_buff, _cmd_stopmode, 8 );

    _cmd_buff[8] = _verify( _cmd_buff, 8 );

    _putchars( _cmd_buff, 9 );
}
//----------------------------------------------------------------------------------------------------------------------
void wepdl::handShake  ( void )
{
    memcpy( _cmd_buff, _cmd_handshake, 8 );

    _cmd_buff[8] = _verify( _cmd_buff, 8 );

    _putchars( _cmd_buff, 9 );
}
//----------------------------------------------------------------------------------------------------------------------
void wepdl::reset( void )
{
    digitalWrite( _reset, LOW );
    delayMicroseconds( 10 );

    digitalWrite( _reset, HIGH );
    delayMicroseconds( 500 );

    digitalWrite( _reset, LOW );
    delay( 3000 );
}
//----------------------------------------------------------------------------------------------------------------------
void wepdl::wakeUp     ( void )
{
    digitalWrite( _wake_up, LOW );
    delayMicroseconds( 10 );

    digitalWrite( _wake_up, HIGH );
    delayMicroseconds( 500 );

    digitalWrite( _wake_up, LOW );
    delay( 10 );
}
//----------------------------------------------------------------------------------------------------------------------
void wepdl::readBaud   ( void )
{
    memcpy( _cmd_buff, _cmd_read_baud, 8 );

    _cmd_buff[8] = _verify( _cmd_buff, 8 );

    _putchars( _cmd_buff, 9 );
}
//----------------------------------------------------------------------------------------------------------------------
void wepdl::clearScreen    ( void )
{
    _cmd_buff[0] = 0xA5;
    _cmd_buff[1] = 0x00;
    _cmd_buff[2] = 0x09;
    _cmd_buff[3] = 0x2E;
    _cmd_buff[4] = 0xCC;
    _cmd_buff[5] = 0x33;
    _cmd_buff[6] = 0xC3;
    _cmd_buff[7] = 0x3C;
    _cmd_buff[8] = _verify( _cmd_buff, 8 );

    _putchars( _cmd_buff, 9 );
}
//----------------------------------------------------------------------------------------------------------------------
void wepdl::rotateScreen ( unsigned char mode )
{
    _cmd_buff[0] = 0xA5;
    _cmd_buff[1] = 0x00;
    _cmd_buff[2] = 0x0A;
    _cmd_buff[3] = 0x0D;
    _cmd_buff[4] = mode;
    _cmd_buff[5] = 0xCC;
    _cmd_buff[6] = 0x33;
    _cmd_buff[7] = 0xC3;
    _cmd_buff[8] = 0x3C;
    _cmd_buff[9] = _verify( _cmd_buff, 9 );

    _putchars( _cmd_buff, 10 );
}
//----------------------------------------------------------------------------------------------------------------------
void wepdl::updateScreen   ( void )
{
    memcpy( _cmd_buff, _cmd_update, 8 );

    _cmd_buff[8] = _verify( _cmd_buff, 8 );

    _putchars( _cmd_buff, 9 );
}
//----------------------------------------------------------------------------------------------------------------------
void wepdl::setBaud    ( long baud )
{
    _cmd_buff[0]  = 0xA5;
    _cmd_buff[1]  = 0x00;
    _cmd_buff[2]  = 0x0D;
    _cmd_buff[3]  = 0x01;

    _cmd_buff[4]  = ( baud >> 24 ) & 0xFF;
    _cmd_buff[5]  = ( baud >> 16 ) & 0xFF;
    _cmd_buff[6]  = ( baud >> 8  ) & 0xFF;
    _cmd_buff[7]  =   baud & 0xFF;

    _cmd_buff[8]  = 0xCC;
    _cmd_buff[9]  = 0x33;
    _cmd_buff[10] = 0xC3;
    _cmd_buff[11] = 0x3C;
    _cmd_buff[12] = _verify( _cmd_buff, 12 );

    _putchars( _cmd_buff, 13 );
    delay( 10 );
    SoftSerial->begin( baud );
}
//----------------------------------------------------------------------------------------------------------------------
void wepdl::setColor ( unsigned char color,
                       unsigned char background_color,
                       bool global_color )
{
    _cmd_buff[0]  = 0xA5;
    _cmd_buff[1]  = 0x00;
    _cmd_buff[2]  = 0x0B;
    _cmd_buff[3]  = 0x10;
    _cmd_buff[4]  = color;
    _cmd_buff[5]  = background_color;
    _cmd_buff[6]  = 0xCC;
    _cmd_buff[7]  = 0x33;
    _cmd_buff[8]  = 0xC3;
    _cmd_buff[9]  = 0x3C;
    _cmd_buff[10] = _verify( _cmd_buff, 10 );

    _putchars( _cmd_buff, 11 );

    if ( global_color )
    {
        _global_color = color;
        _global_background_color = background_color;
    }
}
//----------------------------------------------------------------------------------------------------------------------
void wepdl::setFont  ( unsigned char font,
                       unsigned char language )
{
    _cmd_buff[0] = 0xA5;
    _cmd_buff[1] = 0x00;
    _cmd_buff[2] = 0x0A;
    _cmd_buff[3] = language;
    _cmd_buff[4] = font;
    _cmd_buff[5] = 0xCC;
    _cmd_buff[6] = 0x33;
    _cmd_buff[7] = 0xC3;
    _cmd_buff[8] = 0x3C;
    _cmd_buff[9] = _verify( _cmd_buff, 9 );

    _putchars( _cmd_buff, 10 );
}
//----------------------------------------------------------------------------------------------------------------------
void wepdl::setMemory     ( unsigned char mode )
{
    _cmd_buff[0] = 0xA5;
    _cmd_buff[1] = 0x00;
    _cmd_buff[2] = 0x0A;
    _cmd_buff[3] = 0x07;
    _cmd_buff[4] = mode;
    _cmd_buff[5] = 0xCC;
    _cmd_buff[6] = 0x33;
    _cmd_buff[7] = 0xC3;
    _cmd_buff[8] = 0x3C;
    _cmd_buff[9] = _verify( _cmd_buff, 9 );

    _putchars( _cmd_buff, 10 );
}
//----------------------------------------------------------------------------------------------------------------------
void wepdl::displayBitmap  ( int x,
                             int y,
                             const void * p )
{
    int string_size;
    unsigned char * ptr = ( unsigned char * ) p;

    string_size  = strlen( ( const char * ) ptr );
    string_size += 14;

    _cmd_buff[0] = 0xA5;
    _cmd_buff[1] = ( string_size >> 8 ) & 0xFF;
    _cmd_buff[2] =   string_size & 0xFF;
    _cmd_buff[3] = 0x70;
    _cmd_buff[4] = ( x >> 8 ) & 0xFF;
    _cmd_buff[5] =   x & 0xFF;
    _cmd_buff[6] = ( y >> 8 ) & 0xFF;
    _cmd_buff[7] =   y & 0xFF;

    strcpy( ( char * )( &_cmd_buff[8] ), ( const char * ) ptr );

    string_size -= 5;

    _cmd_buff[string_size]     = 0xCC;
    _cmd_buff[string_size + 1] = 0x33;
    _cmd_buff[string_size + 2] = 0xC3;
    _cmd_buff[string_size + 3] = 0x3C;
    _cmd_buff[string_size + 4] = _verify( _cmd_buff, string_size + 4 );

    _putchars( _cmd_buff, string_size + 5 );
}
//----------------------------------------------------------------------------------------------------------------------
void wepdl::displayCharacter ( int x,
                               int y,
                               unsigned char ch )
{
    unsigned char buff[2];
    buff[0] = ch;
    buff[1] = 0;
    displayText( x, y, buff );
}
//----------------------------------------------------------------------------------------------------------------------
void wepdl::displayText ( int x,
                          int y,
                          const void * p )
{
    int string_size;
    unsigned char * ptr = ( unsigned char * ) p;

    string_size = strlen( ( const char * ) ptr );
    string_size += 14;

    _cmd_buff[0] = 0xA5;

    _cmd_buff[1] = ( string_size >> 8 ) & 0xFF;
    _cmd_buff[2] =   string_size & 0xFF;

    _cmd_buff[3] = 0x30;

    _cmd_buff[4] = ( x >> 8 ) & 0xFF;
    _cmd_buff[5] =   x & 0xFF;
    _cmd_buff[6] = ( y >> 8 ) & 0xFF;
    _cmd_buff[7] =   y & 0xFF;

    strcpy( ( char * )( &_cmd_buff[8] ), ( const char * ) ptr );

    string_size -= 5;

    _cmd_buff[string_size]     = 0xCC;
    _cmd_buff[string_size + 1] = 0x33;
    _cmd_buff[string_size + 2] = 0xC3;
    _cmd_buff[string_size + 3] = 0x3C;
    _cmd_buff[string_size + 4] = _verify( _cmd_buff, string_size + 4 );
    _putchars( _cmd_buff, string_size + 5 );
}
//----------------------------------------------------------------------------------------------------------------------
void wepdl::Picture ( void )
{
    memcpy( _cmd_buff, _cmd_load_pic, 8 );

    _cmd_buff[8] = _verify( _cmd_buff, 8 );

    _putchars( _cmd_buff, 9 );
}
//----------------------------------------------------------------------------------------------------------------------
void wepdl::FontLoad    ( void )
{
    memcpy( _cmd_buff, _cmd_load_font, 8 );

    _cmd_buff[8] = _verify( _cmd_buff, 8 );

    _putchars( _cmd_buff, 9 );
}
//----------------------------------------------------------------------------------------------------------------------
void wepdl::drawPixel     ( int x,
                            int y )
{
    _cmd_buff[0]  = 0xA5;
    _cmd_buff[1]  = 0x00;
    _cmd_buff[2]  = 0x0D;
    _cmd_buff[3]  = 0x20;
    _cmd_buff[4]  = ( x >> 8 ) & 0xFF;
    _cmd_buff[5]  =   x & 0xFF;
    _cmd_buff[6]  = ( y >> 8 ) & 0xFF;
    _cmd_buff[7]  =   y & 0xFF;
    _cmd_buff[8]  = 0xCC;
    _cmd_buff[9]  = 0x33;
    _cmd_buff[10] = 0xC3;
    _cmd_buff[11] = 0x3C;
    _cmd_buff[12] = _verify( _cmd_buff, 12 );

    _putchars( _cmd_buff, 13 );
}
//----------------------------------------------------------------------------------------------------------------------
void wepdl::drawLine      ( int A_x,
                            int A_y,
                            int B_x,
                            int B_y,
                            int thickness )
{
    int counter = 1,
        Ax      = A_x,
        Ay      = A_y,
        Bx      = B_x,
        By      = B_y;

    for ( counter = 1; counter <= thickness; counter++ )
    {
        _cmd_buff[0]  = 0xA5;
        _cmd_buff[1]  = 0x00;
        _cmd_buff[2]  = 0x11;
        _cmd_buff[3]  = 0x22;
        _cmd_buff[4]  = ( Ax >> 8 ) & 0xFF;
        _cmd_buff[5]  =   Ax & 0xFF;
        _cmd_buff[6]  = ( Ay >> 8 ) & 0xFF;
        _cmd_buff[7]  =   Ay & 0xFF;
        _cmd_buff[8]  = ( Bx >> 8 ) & 0xFF;
        _cmd_buff[9]  =   Bx & 0xFF;
        _cmd_buff[10] = ( By >> 8 ) & 0xFF;
        _cmd_buff[11] =   By & 0xFF;
        _cmd_buff[12] = 0xCC;
        _cmd_buff[13] = 0x33;
        _cmd_buff[14] = 0xC3;
        _cmd_buff[15] = 0x3C;
        _cmd_buff[16] = _verify( _cmd_buff, 16 );

        _putchars( _cmd_buff, 17 );

        if        ( A_y == B_y ) { Ay++; By++; }
        else if   ( A_x == B_x ) { Ax++; Bx++; }
        else if ( ( A_x != B_x ) && ( A_y != B_y ) )
             {
                 if      ( A_y < B_y ) { Ax++; Bx++; Ay--; By--; }
                 else if ( A_y > B_y ) { Ax++; Bx++; Ay++; By++; };
             };
    }
}
//----------------------------------------------------------------------------------------------------------------------
void wepdl::drawCircle    ( int x,
                            int y,
                            int radius,
                            bool fill )
{
    _cmd_buff[0]  = 0xA5;
    _cmd_buff[1]  = 0x00;
    _cmd_buff[2]  = 0x0F;

    if (fill) { _cmd_buff[3] = 0x27; }
    else      { _cmd_buff[3] = 0x26; };

    _cmd_buff[4]  = ( x >> 8 ) & 0xFF;
    _cmd_buff[5]  =   x & 0xFF;
    _cmd_buff[6]  = ( y >> 8 ) & 0xFF;
    _cmd_buff[7]  =   y & 0xFF;
    _cmd_buff[8]  = ( radius >> 8 ) & 0xFF;
    _cmd_buff[9]  =   radius & 0xFF;
    _cmd_buff[10] = 0xCC;
    _cmd_buff[11] = 0x33;
    _cmd_buff[12] = 0xC3;
    _cmd_buff[13] = 0x3C;
    _cmd_buff[14] = _verify( _cmd_buff, 14 );

    _putchars( _cmd_buff, 15 );
}
//----------------------------------------------------------------------------------------------------------------------
void wepdl::drawRing    ( int x,
                          int y,
                          int radius,
                          int border,
                          unsigned char color,
                          unsigned char background_color )
{
    setColor   ( color, background_color, false );
    drawCircle ( x, y, radius, true );

    setColor   ( background_color, color, false );
    drawCircle ( x, y, ( ( border - radius ) * -1 ), true );

    setColor   ( _global_color, _global_background_color );
}
//----------------------------------------------------------------------------------------------------------------------
void wepdl::drawTriangle  ( int A_x,
                            int A_y,
                            int B_x,
                            int B_y,
                            int C_x,
                            int C_y,
                            bool fill )
{
    _cmd_buff[0]  = 0xA5;
    _cmd_buff[1]  = 0x00;
    _cmd_buff[2]  = 0x15;

      if (fill)  { _cmd_buff[3] = 0x29; }
      else       { _cmd_buff[3] = 0x28; };

    _cmd_buff[4]  = ( A_x >> 8 ) & 0xFF;
    _cmd_buff[5]  =   A_x & 0xFF;
    _cmd_buff[6]  = ( A_y >> 8 ) & 0xFF;
    _cmd_buff[7]  =   A_y & 0xFF;
    _cmd_buff[8]  = ( B_x >> 8 ) & 0xFF;
    _cmd_buff[9]  =   B_x & 0xFF;
    _cmd_buff[10] = ( B_y >> 8 ) & 0xFF;
    _cmd_buff[11] =   B_y & 0xFF;
    _cmd_buff[12] = ( C_x >> 8 ) & 0xFF;
    _cmd_buff[13] =   C_x & 0xFF;
    _cmd_buff[14] = ( C_y >> 8 ) & 0xFF;
    _cmd_buff[15] =   C_y & 0xFF;
    _cmd_buff[16] = 0xCC;
    _cmd_buff[17] = 0x33;
    _cmd_buff[18] = 0xC3;
    _cmd_buff[19] = 0x3C;
    _cmd_buff[20] = _verify( _cmd_buff, 20 );

    _putchars( _cmd_buff, 21 );
}
//----------------------------------------------------------------------------------------------------------------------
void wepdl::drawRectangle ( int A_x,
                            int A_y,
                            int C_x,
                            int C_y,
                            bool fill )
{
    _cmd_buff[0]  = 0xA5;
    _cmd_buff[1]  = 0x00;
    _cmd_buff[2]  = 0x11;

    if (fill)  { _cmd_buff[3] = 0x24; }
    else       { _cmd_buff[3] = 0x25; };

    _cmd_buff[4]  = ( A_x >> 8 ) & 0xFF;
    _cmd_buff[5]  =   A_x & 0xFF;
    _cmd_buff[6]  = ( A_y >> 8 ) & 0xFF;
    _cmd_buff[7]  =   A_y & 0xFF;
    _cmd_buff[8]  = ( C_x >> 8 ) & 0xFF;
    _cmd_buff[9]  =   C_x & 0xFF;
    _cmd_buff[10] = ( C_y >> 8 ) & 0xFF;
    _cmd_buff[11] =   C_y & 0xFF;
    _cmd_buff[12] = 0xCC;
    _cmd_buff[13] = 0x33;
    _cmd_buff[14] = 0xC3;
    _cmd_buff[15] = 0x3C;
    _cmd_buff[16] = _verify( _cmd_buff, 16 );

    _putchars( _cmd_buff, 17 );
}
//----------------------------------------------------------------------------------------------------------------------




