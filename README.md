# waveshare-epd-library (wepdl)

Waveshare Electronic Paper Display Library Class

<img src="wepdl_screen.jpg" />

---

### Prerequisites

What you need to use this library

```
- Arduino-IDE (I'm using 1.8.2 and 1.9.0 Beta 31)
- wepdl library (you will find it in waweshare_epd_example/WEPDL folder)
- Waveshare 4.3" e-ink display (UART - not SPI)
- One of : (I checked only on those devices and this library works on them)
  - Arduino Nano (clone)
  - Arduino Uno  (clone)
  - Lolin NodeMcu v3
```

---

### Installing

Download repository and copy folder WEPDL to Arduino library folder

```

git clone https://github.com/tmseth/waveshare-epd-library.git

cp -r waveshare-epd-library/waweshare_epd_example/WEPDL /home/YourUserName/Arduino/libraries/
```

---

## Running the tests

Run Arduino-IDE, from menu "File" choice "Open" and find sketch "waweshare_epd_example.ino"

Location : waveshare-epd-library/waweshare_epd_example/waweshare_epd_example.ino

1) Connect your device (Arduino, Nodemcu, etc) to computer.

2) Choice USB port.

3) In Arduino-IDE use combination CTRL + U to compile and upload sketch.

4) Wait a moment :)

---

## Code examples

This information will be placed ultimately in the Wiki.

This library was created using oryginal library from Waveshare ( epd.cpp and epd.h ).

---

### Creating new class object

```

#include "wepdl.h"
//----------------------------------------------------------------------------------------------------------------------
//         PIN     Nodemcu v3 (lolin) | Arduino UNO |
//----------------------------------------------------------------------------------------------------------------------
#define    RX      D7 // ( GPIO13 )   |    10       |
#define    TX      D8 // ( GPIO15 )   |    11       |
#define    WAKEUP  D6 // ( GPIO12 )   |     2       |
#define    RESET   D5 // ( GPIO14 )   |     3       |
//----------------------------------------------------------------------------------------------------------------------
wepdl * EPD = new wepdl( RX, TX, WAKEUP, RESET );

```

---

### Using object

```

EPD->initialize();                     // Initialize comunication with device
EPD->wakeUp();                         // Wake up device
EPD->reset();                          // Reset device
EPD->setMemory     ( MICROSD );        // Set memory to MICROSD    (    MICROSD / FLASH )
EPD->rotateScreen  ( VERTICAL );       // Set rotation to VERTICAL ( HORIZONTAL / VERTICAL )
EPD->clearScreen();                    // Clear screen
```
---

### Defined variables

```

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
```

---

### Methods description



#### initialize ( void )

#### goSleep ( void )

#### handShake ( void )

#### reset ( void )

#### wakeUp ( void )

#### readBaud ( void )

#### clearScreen ( void )

#### rotateScreen ( unsigned char mode )

#### updateScreen ( void )

#### setBaud ( long baud )

#### setColor ( unsigned char color, unsigned char background_color, bool global_color = true )

#### setFont ( unsigned char font, unsigned char language = ENGLISH )

#### setMemory ( unsigned char mode )

#### displayBitmap ( int x, int y, const void * p )

#### displayCharacter( int x, int y, unsigned char ch )

#### displayText ( int x, int y, const void * p )

#### Picture ( void )

#### FontLoad ( void )

#### drawPixel ( int x, int y )

#### drawLine ( int A_x, int A_y, int B_x, int B_y, int thickness = 1 )

#### drawCircle ( int x, int y, int radius, bool fill = false )

#### drawRing ( int x, int y, int radius, int border, unsigned char color, unsigned char background_color )

#### drawTriangle ( int A_x, int A_y, int B_x, int B_y, int C_x, int C_y, bool fill = false )

#### drawRectangle ( int A_x, int A_y, int C_x, int C_y, bool fill = false )

---

### Drawning and displaing elements

```

EPD->displayBitmap ( 0, 400, "M001.BMP" );      // Display bitmap


```

### Updating screen

```

EPD->updateScreen();          // Update screen and display everything from last Screen update
EPD->goSleep();               // Go to sleep mode
```


---

## Authors

* **Tadeusz Miszczyk** - *This EPD library*
* **Waveshare** - *Initial work with oryginal EPD library*

---

## Waveshare

Website : [https://www.waveshare.com](https://www.waveshare.com)

E-mail : [service@waveshare.com](mailto:service@waveshare.com)

---

Waveshare demo video on YouTube : [https://www.youtube.com/watch?v=06rDuQzYovk](https://www.youtube.com/watch?v=06rDuQzYovk)

Waveshare 4.3" e-paper display UART module : [https://www.waveshare.com/4.3inch-e-paper.htm](https://www.waveshare.com/4.3inch-e-paper.htm) (800x600 px, 4 color)

Wiki :  [https://www.waveshare.com/wiki/4.3inch_e-Paper_UART_Module](https://www.waveshare.com/wiki/4.3inch_e-Paper_UART_Module)

Datasheets of parts : [https://www.waveshare.com/wiki/4.3inch_e-Paper_Datasheets](https://www.waveshare.com/wiki/4.3inch_e-Paper_Datasheets)

Oryginal library : [https://www.waveshare.com/w/upload/archive/e/eb/20171228082252%214.3inch-e-Paper-Code.7z](https://www.waveshare.com/w/upload/archive/e/eb/20171228082252%214.3inch-e-Paper-Code.7z)

User manual : [https://www.waveshare.com/wiki/File:4.3inch-e-Paper-UserManual.pdf](https://www.waveshare.com/wiki/File:4.3inch-e-Paper-UserManual.pdf)

---

## License

This project is licensed under the GNU General Public License v3.0 - see the [LICENSE](LICENSE) file for details

---

## Acknowledgments

* Inspiration : Life

---
