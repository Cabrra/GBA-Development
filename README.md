Pixel Manipulation
==================

## Overview

![Hello World GBA](https://github.com/Cabrra/cabrra.github.io/blob/master/Images/Hello_world.png)

1. Hello World & buffered input
+ Unsigned short pointer to memory address 0x04000000: this is the display control register bit flags are located. Flags: 0x3 for mode 3 and 0x400 for background 2. 
+ Unsigned short pointer to memory address 0x06000000: it points to the beginning of the pixel map which will be displayed on the screen. Each pixel is represented by a 16-bit number for a 15-bit color value. 
+ Volatile unsigned short pointer to memory address 0x04000130: it is volatile because the hardware changes these bits. Used to check the button states. 
+ My GBA defined buttons: Arrow keys/Enter/Backspace/Z/X/A/S

## Built With

* [VisualHAM](https://www.dwheeler.com/gba/) - C development for gba rooms
* Run with GBA emulator executable .gba file

## Contributing

Please read [CONTRIBUTING.md](https://github.com/Cabrra/Contributing-template/blob/master/Contributing-template.md) for details on the code of conduct, and the process for submitting pull requests to me.

## Authors

* **Jagoba "Jake" Marcos** - [Cabrra](https://github.com/Cabrra)

## License

This project is licensed under the MIT license - see the [LICENSE](LICENSE) file for details

## Acknowledgments

* Full Sail University - Game Development Department
* Richard E. Arndt - [email](volvoom@gmail.com)