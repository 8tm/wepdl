/*********************************************************************************************************
*
*    File             : wepdl.h
*    Environment      : Arduino Uno/Nano; Lolin Nodemcu v3
*    Version          : V1.0
*    Created by       : Tadeusz Miszczyk (tadeusz.miszczyk[at]gmail.com)
*
*********************************************************************************************************/
#include "wepdl.h"
#include <Arduino.h>
#include <SoftwareSerial.h>
//---------------------------------------------------------------------------------------------------------------------- 
extern "C" {
#include "user_interface.h"
}
//---------------------------------------------------------------------------------------------------------------------- 
wepdl :: wepdl ( uint8_t rx, uint8_t tx, uint8_t wakeup, uint8_t reset )
{
    _wakeup    = wakeup;
    _reset     = reset;
    SoftSerial = new SoftwareSerial( rx, tx );
}
//---------------------------------------------------------------------------------------------------------------------- 
void wepdl::_putchars(const unsigned char * ptr, int n)
{
    int i, x;
    for(i = 0; i < n; i++)
    {
        x = ptr[i];
        SoftSerial->write(x);
    }
}
//---------------------------------------------------------------------------------------------------------------------- 
unsigned char wepdl::_verify(const void * ptr, int n)
{
    int i;
    unsigned char * p = (unsigned char *)ptr;
    unsigned char result;
    for(i = 0, result = 0; i < n; i++)
    {
        result ^= p[i];
    }
    return result;
}
//---------------------------------------------------------------------------------------------------------------------- 
// sprawdzenie dostępności wyświetlacza
void wepdl::HandShake  ( void )
{
    memcpy(_cmd_buff, _cmd_handshake, 8);
    _cmd_buff[8] = _verify(_cmd_buff, 8);
    _putchars(_cmd_buff, 9);
}
//---------------------------------------------------------------------------------------------------------------------- 
// inicjalizacja wyświetlacza
void wepdl::Initialize ( void )
{
    SoftSerial->begin(115200);
    pinMode(_wakeup, HIGH);
    pinMode(_reset, HIGH);
}
//---------------------------------------------------------------------------------------------------------------------- 
// wybór nośnika pamięci : MEM_NAND lub MEM_TF
void wepdl::Memory     ( unsigned char mode )
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
    _cmd_buff[9] = _verify(_cmd_buff, 9);
    _putchars(_cmd_buff, 10);        
}

//----------------------------------------------------------------------------------------------------------------------
void wepdl::Reset( void )                                      /* Reseting Display */
{   
    digitalWrite(_reset, LOW);
    delayMicroseconds(10);

    digitalWrite(_reset, HIGH);
    delayMicroseconds(500);
    
    digitalWrite(_reset, LOW);
    delay(3000);
}
//---------------------------------------------------------------------------------------------------------------------- 
// przejście w stan zatrzymania
void wepdl::Go_Sleep       ( void )
{
    memcpy(_cmd_buff, _cmd_stopmode, 8);
    _cmd_buff[8] = _verify(_cmd_buff, 8);
    _putchars(_cmd_buff, 9);

}
//---------------------------------------------------------------------------------------------------------------------- 
// obudzenie wyświetlacza
void wepdl::Wake_Up     ( void )
{
    digitalWrite(_wakeup, LOW);
    delayMicroseconds(10);
    digitalWrite(_wakeup, HIGH);
    delayMicroseconds(500);
    digitalWrite(_wakeup, LOW);
    delay(10);
}
//---------------------------------------------------------------------------------------------------------------------- 
// set uart baud
void wepdl::SetBaud    ( long baud )
{
    _cmd_buff[0] = 0xA5;
    _cmd_buff[1] = 0x00;
    _cmd_buff[2] = 0x0D;    
    _cmd_buff[3] = 0x01;    
    
    _cmd_buff[4] = (baud >> 24) & 0xFF;
    _cmd_buff[5] = (baud >> 16) & 0xFF;
    _cmd_buff[6] = (baud >> 8) & 0xFF;
    _cmd_buff[7] = baud & 0xFF;
    
    _cmd_buff[8] = 0xCC;
    _cmd_buff[9] = 0x33;
    _cmd_buff[10] = 0xC3;
    _cmd_buff[11] = 0x3C;    
    _cmd_buff[12] = _verify(_cmd_buff, 12);
    _putchars(_cmd_buff, 13);    
    delay(10);    
    SoftSerial->begin(baud);
}
//---------------------------------------------------------------------------------------------------------------------- 
// read uart baud
void wepdl::ReadBaud   ( void )
{
    memcpy(_cmd_buff, _cmd_read_baud, 8);
    _cmd_buff[8] = _verify(_cmd_buff, 8);
    _putchars(_cmd_buff, 9);
}
//---------------------------------------------------------------------------------------------------------------------- 
// rysowanie okręgu lub wypełnionego okręgu
void wepdl::drawCircle    ( int x0, int y0, int r, bool fill)
{
    _cmd_buff[0] = 0xA5;
    _cmd_buff[1] = 0x00;
    _cmd_buff[2] = 0x0F;    

    if (fill)
        _cmd_buff[3] = 0x27; // CMD_FILL_CIRCLE;
    else
        _cmd_buff[3] = 0x26; // CMD_DRAW_CIRCLE;
    
    _cmd_buff[4] = (x0 >> 8) & 0xFF;
    _cmd_buff[5] = x0 & 0xFF;
    _cmd_buff[6] = (y0 >> 8) & 0xFF;
    _cmd_buff[7] = y0 & 0xFF;
    _cmd_buff[8] = (r >> 8) & 0xFF;
    _cmd_buff[9] = r & 0xFF;
    
    _cmd_buff[10] = 0xCC;
    _cmd_buff[11] = 0x33;
    _cmd_buff[12] = 0xC3;
    _cmd_buff[13] = 0x3C;    
    _cmd_buff[14] = _verify(_cmd_buff, 14);
    _putchars(_cmd_buff, 15);
}
//---------------------------------------------------------------------------------------------------------------------- 
// rysowanie obręczy
void wepdl::drawRing    ( int x0, int y0, int r, int border, unsigned char color, unsigned char bkcolor)
{
    Color  ( color, bkcolor, false );
    drawCircle ( x0, y0, r, true );
    Color  ( bkcolor, color, false );
    drawCircle ( x0, y0, ( ( border - r ) * -1 ), true );
    Color  ( _global_color, _global_background_color );
}
//---------------------------------------------------------------------------------------------------------------------- 
// rysowanie linii
void wepdl::drawLine      ( int x0, int y0, int x1, int y1 )
{
    _cmd_buff[0] = 0xA5;
    _cmd_buff[1] = 0x00;
    _cmd_buff[2] = 0x11;    
    _cmd_buff[3] = 0x22;    
    
    _cmd_buff[4] = (x0 >> 8) & 0xFF;
    _cmd_buff[5] = x0 & 0xFF;
    _cmd_buff[6] = (y0 >> 8) & 0xFF;
    _cmd_buff[7] = y0 & 0xFF;
    _cmd_buff[8] = (x1 >> 8) & 0xFF;
    _cmd_buff[9] = x1 & 0xFF;
    _cmd_buff[10] = (y1 >> 8) & 0xFF;
    _cmd_buff[11] = y1 & 0xFF;    
    
    _cmd_buff[12] = 0xCC;
    _cmd_buff[13] = 0x33;
    _cmd_buff[14] = 0xC3;
    _cmd_buff[15] = 0x3C;    
    _cmd_buff[16] = _verify(_cmd_buff, 16);
    _putchars(_cmd_buff, 17);    
}
//---------------------------------------------------------------------------------------------------------------------- 
// rysowanie punktu
void wepdl::drawPixel     ( int x0, int y0 )
{
    _cmd_buff[0] = 0xA5;
    _cmd_buff[1] = 0x00;
    _cmd_buff[2] = 0x0D;    
    _cmd_buff[3] = 0x20;    
    
    _cmd_buff[4] = (x0 >> 8) & 0xFF;
    _cmd_buff[5] = x0 & 0xFF;
    _cmd_buff[6] = (y0 >> 8) & 0xFF;
    _cmd_buff[7] = y0 & 0xFF;
    
    _cmd_buff[8] = 0xCC;
    _cmd_buff[9] = 0x33;
    _cmd_buff[10] = 0xC3;
    _cmd_buff[11] = 0x3C;    
    _cmd_buff[12] = _verify(_cmd_buff, 12);
    _putchars(_cmd_buff, 13);
}
//---------------------------------------------------------------------------------------------------------------------- 
// rysowanie wypełnionego prostokąta
void wepdl::drawRectangle ( int x0, int y0, int x1, int y1, bool fill )
{
    if (fill)
    {
        _cmd_buff[0] = 0xA5;
        _cmd_buff[1] = 0x00;
        _cmd_buff[2] = 0x11;
        _cmd_buff[3] = 0x24;
        _cmd_buff[4] = (x0 >> 8) & 0xFF;
        _cmd_buff[5] = x0 & 0xFF;
        _cmd_buff[6] = (y0 >> 8) & 0xFF;
        _cmd_buff[7] = y0 & 0xFF;
        _cmd_buff[8] = (x1 >> 8) & 0xFF;
        _cmd_buff[9] = x1 & 0xFF;
        _cmd_buff[10] = (y1 >> 8) & 0xFF;
        _cmd_buff[11] = y1 & 0xFF;
        _cmd_buff[12] = 0xCC;
        _cmd_buff[13] = 0x33;
        _cmd_buff[14] = 0xC3;
        _cmd_buff[15] = 0x3C;
        _cmd_buff[16] = _verify(_cmd_buff, 16);
        _putchars(_cmd_buff, 17);
    }else{
            drawLine ( x0, y0, x1, y0 );
            drawLine ( x1, y0, x1, y1 );
            drawLine ( x1, y1, x0, y1 );
            drawLine ( x0, y1, x0, y0 );
         };   
}
//---------------------------------------------------------------------------------------------------------------------- 
// rysowanie pustego lub wypełnionego trójkąta
void wepdl::drawTriangle  ( int x0, int y0, int x1, int y1, int x2, int y2, bool fill )
{
    _cmd_buff[0] = 0xA5;
    _cmd_buff[1] = 0x00;
    _cmd_buff[2] = 0x15;

      if (fill)  {  _cmd_buff[3] = 0x29; }
      else       {  _cmd_buff[3] = 0x28; };

    _cmd_buff[4] = (x0 >> 8) & 0xFF;
    _cmd_buff[5] = x0 & 0xFF;
    _cmd_buff[6] = (y0 >> 8) & 0xFF;
    _cmd_buff[7] = y0 & 0xFF;
    _cmd_buff[8] = (x1 >> 8) & 0xFF;
    _cmd_buff[9] = x1 & 0xFF;
    _cmd_buff[10] = (y1 >> 8) & 0xFF;
    _cmd_buff[11] = y1 & 0xFF;    
    _cmd_buff[12] = (x2 >> 8) & 0xFF;
    _cmd_buff[13] = x2 & 0xFF;
    _cmd_buff[14] = (y2 >> 8) & 0xFF;
    _cmd_buff[15] = y2 & 0xFF;
    _cmd_buff[16] = 0xCC;
    _cmd_buff[17] = 0x33;
    _cmd_buff[18] = 0xC3;
    _cmd_buff[19] = 0x3C;    
    _cmd_buff[20] = _verify(_cmd_buff, 20);
    _putchars(_cmd_buff, 21);    
}
//---------------------------------------------------------------------------------------------------------------------- 
// wyświetlenie obrazu
void wepdl::Bitmap  ( const void * p, int x0, int y0 )
{
    int string_size;
    unsigned char * ptr = (unsigned char *)p;
    
    string_size = strlen((const char *)ptr);
    string_size += 14;
    
    _cmd_buff[0] = 0xA5;
    
    _cmd_buff[1] = (string_size >> 8) & 0xFF;
    _cmd_buff[2] = string_size & 0xFF;
    
    _cmd_buff[3] = 0x70;
    
    _cmd_buff[4] = (x0 >> 8) & 0xFF;
    _cmd_buff[5] = x0 & 0xFF;
    _cmd_buff[6] = (y0 >> 8) & 0xFF;
    _cmd_buff[7] = y0 & 0xFF;
    
    strcpy((char *)(&_cmd_buff[8]), (const char *)ptr);
    
    string_size -= 5;
    
    _cmd_buff[string_size] = 0xCC;
    _cmd_buff[string_size + 1] = 0x33;
    _cmd_buff[string_size + 2] = 0xC3;
    _cmd_buff[string_size + 3] = 0x3C;
    _cmd_buff[string_size + 4] = _verify(_cmd_buff, string_size + 4);
    _putchars(_cmd_buff, string_size + 5);    
}
//---------------------------------------------------------------------------------------------------------------------- 
// wczytanie czcionki z pamięci
void wepdl::Font_load    ( void )
{
    memcpy(_cmd_buff, _cmd_load_font, 8);
    _cmd_buff[8] = _verify(_cmd_buff, 8);
    _putchars(_cmd_buff, 9);
}
//---------------------------------------------------------------------------------------------------------------------- 
// wczytanie obrazu z pamięci
void wepdl::Picture ( void )
{
    memcpy(_cmd_buff, _cmd_load_pic, 8);
    _cmd_buff[8] = _verify(_cmd_buff, 8);
    _putchars(_cmd_buff, 9);
}
//---------------------------------------------------------------------------------------------------------------------- 
// wyświetlenie znaku
void wepdl::Character ( unsigned char ch, int x0, int y0 )
{
    unsigned char buff[2];
    buff[0] = ch;
    buff[1] = 0;
    Text(buff, x0, y0);
}
//---------------------------------------------------------------------------------------------------------------------- 
// wyświetlenie ciągu znaków
void wepdl::Text      ( const void * p, int x0, int y0 )
{
    int string_size;
    unsigned char * ptr = (unsigned char *)p;
    
    string_size = strlen((const char *)ptr);
    string_size += 14;
    
    _cmd_buff[0] = 0xA5;
    
    _cmd_buff[1] = (string_size >> 8) & 0xFF;
    _cmd_buff[2] = string_size & 0xFF;
    
    _cmd_buff[3] = 0x30;
    
    _cmd_buff[4] = (x0 >> 8) & 0xFF;
    _cmd_buff[5] = x0 & 0xFF;
    _cmd_buff[6] = (y0 >> 8) & 0xFF;
    _cmd_buff[7] = y0 & 0xFF;
    
    strcpy((char *)(&_cmd_buff[8]), (const char *)ptr);
    
    string_size -= 5;
    
    _cmd_buff[string_size] = 0xCC;
    _cmd_buff[string_size + 1] = 0x33;
    _cmd_buff[string_size + 2] = 0xC3;
    _cmd_buff[string_size + 3] = 0x3C;
    _cmd_buff[string_size + 4] = _verify(_cmd_buff, string_size + 4);
    _putchars(_cmd_buff, string_size + 5);
}
//---------------------------------------------------------------------------------------------------------------------- 
// czyszczenie ekranu - używa koloru tła - sprawdzić czy użyje np GRAY :)
void wepdl::Clear_Screen    ( void )
{
    _cmd_buff[0] = 0xA5;
    _cmd_buff[1] = 0x00;
    _cmd_buff[2] = 0x09;    
    _cmd_buff[3] = 0x2E;
    _cmd_buff[4] = 0xCC;
    _cmd_buff[5] = 0x33;
    _cmd_buff[6] = 0xC3;
    _cmd_buff[7] = 0x3C;    
    _cmd_buff[8] = _verify(_cmd_buff, 8);
    _putchars(_cmd_buff, 9);    
}
//---------------------------------------------------------------------------------------------------------------------- 
// obrót wyświetlacza : EPD_NORMAL lub EPD_INVERSION
void wepdl::Rotate_Screen ( unsigned char mode )
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
    _cmd_buff[9] = _verify(_cmd_buff, 9);
    _putchars(_cmd_buff, 10);    
}
//---------------------------------------------------------------------------------------------------------------------- 
// odświeżenie obrazu
void wepdl::Update_Screen   ( void )
{
    memcpy(_cmd_buff, _cmd_update, 8);
    _cmd_buff[8] = _verify(_cmd_buff, 8);
    _putchars(_cmd_buff, 9);
}
//---------------------------------------------------------------------------------------------------------------------- 
// ustawienie koloru i tła : WHITE, GRAY, DARK_GRAY, BLACK
void wepdl::Color ( unsigned char color, unsigned char bkcolor, bool global_color )
{
    _cmd_buff[0] = 0xA5;
    _cmd_buff[1] = 0x00;
    _cmd_buff[2] = 0x0B;
    _cmd_buff[3] = 0x10;
    _cmd_buff[4] = color;
    _cmd_buff[5] = bkcolor;
    _cmd_buff[6] = 0xCC;
    _cmd_buff[7] = 0x33;
    _cmd_buff[8] = 0xC3;
    _cmd_buff[9] = 0x3C;
    _cmd_buff[10] = _verify(_cmd_buff, 10);
    _putchars(_cmd_buff, 11);
    
    if (global_color)
    {
        _global_color = color;
        _global_background_color = bkcolor;
    }
}
//---------------------------------------------------------------------------------------------------------------------- 
// wybór czcionki angielskiej lub chińskiej : ASCII32 or ASCII48 or ASCII64 or GBK32 or GBK48 or GBK64
void wepdl::Font  ( unsigned char Font, unsigned char Language )
{
    _cmd_buff[0] = 0xA5; 
    _cmd_buff[1] = 0x00;
    _cmd_buff[2] = 0x0A;    
    _cmd_buff[3] = Language;
    _cmd_buff[4] = Font;
    _cmd_buff[5] = 0xCC;
    _cmd_buff[6] = 0x33;
    _cmd_buff[7] = 0xC3;
    _cmd_buff[8] = 0x3C;    
    _cmd_buff[9] = _verify(_cmd_buff, 9);
    _putchars(_cmd_buff, 10);
}
//---------------------------------------------------------------------------------------------------------------------- 
