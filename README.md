# waveshare-epd-library (wepdl)

Waveshare Electronic Paper Display Library Class

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisites

What you need to use this library

```
- Arduino-IDE (I'm using 1.8.2 and 1.9.0 Beta 31)
- wepdl library (you will find it in waweshare_epd_example/WEPDL folder)
- Waveshare 4.3" e-ink display (UART - not SPI)
- One of :
  - Arduino Nano      (I checked on this device and it works)
  - Arduino Uno       (I checked on this device and it works)
  - Lolin NodeMcu v3  (I checked on this device and it works)
```

### Installing

Download repository and copy folder WEPDL to Arduino library folder

```

git clone https://github.com/tmseth/waveshare-epd-library.git

cp -r waveshare-epd-library/waweshare_epd_example/WEPDL /home/YourUserName/Arduino/libraries
```

## Running the tests

Run Arduino-IDE, from menu "File" choice "Open" and find sketch "waweshare_epd_example.ino"

In downloaded repository : waveshare-epd-library/waweshare_epd_example/waweshare_epd_example.ino

Connect your device (Arduino, Nodemcu, etc) to computer.

In Arduino-IDE use combination CTRL + U to compile and upload sketch.

Wait a moment :)

### Code

This library was created using oryginal library from Waveshare ( epd.cpp and epd.h ).

```
Give an example
```

## Built With

* [Dropwizard](http://www.dropwizard.io/1.0.2/docs/) - The web framework used
* [Maven](https://maven.apache.org/) - Dependency Management
* [ROME](https://rometools.github.io/rome/) - Used to generate RSS Feeds

## Contributing

Please read [CONTRIBUTING.md](https://gist.github.com/PurpleBooth/b24679402957c63ec426) for details on our code of conduct, and the process for submitting pull requests to us.

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/your/project/tags).

## Authors

* **Waveshare** - *Initial work with oryginal EPD library* - epd.cpp and epd.h
[Download Waveshare oryginal library](https://link.to.files)
* **Tadeusz Miszczyk** - *this version of EPD library*


[PurpleBooth](https://github.com/PurpleBooth)

See also the list of [contributors](https://github.com/your/project/contributors) who participated in this project.

## License

This project is licensed under the GNU General Public License v3.0 - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* Hat tip to anyone who's code was used
* Inspiration : Life
* etc
