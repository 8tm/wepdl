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

### Code examples

This library was created using oryginal library from Waveshare ( epd.cpp and epd.h ).

```

TO DO :(

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
