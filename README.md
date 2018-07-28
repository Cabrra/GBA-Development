Pixel Manipulation
==================

## Overview

1. Hello World & buffered input

![Hello World GBA](https://github.com/Cabrra/cabrra.github.io/blob/master/Images/hello_world.png)

+ Unsigned short pointer to memory address 0x04000000: this is the display control register bit flags are located. Flags: 0x3 for mode 3 and 0x400 for background 2. 
+ Unsigned short pointer to memory address 0x06000000: it points to the beginning of the pixel map which will be displayed on the screen. Each pixel is represented by a 16-bit number for a 15-bit color value. 
+ Volatile unsigned short pointer to memory address 0x04000130: it is volatile because the hardware changes these bits. Used to check the button states. 
+ My GBA defined buttons: Arrow keys/Enter/Backspace/Z/X/A/S

2.Bitmaps

![Bitmaps GBA](https://github.com/Cabrra/cabrra.github.io/blob/master/Images/bitmaps.png)

+ Mode 3 and background 2. Memory allocated in EWRAM (EXRAM) for the back buffer.
+ Draw_Clear function: clears the back buffer to a particular color in a for loop. 
+ Draw_Pixel function: Plots a pixel anywhere on the back buffer (used to draw the bitmap). 
+ Draw_WaitVBlank function: Waits until the beginning of the vertical blank period.
+ Draw_Present function: copies the entire back buffer to the front buffer during vblank to avoid visual artifacts.
+ Screen is set to a different color every frame; starting with color=0, and then it increments by +8 on every frame. 
+ Controls: 
	+ When holding down the “DOWN” button, the present function gets faster (no screen artifacts because is presented fast enough during vertical blank). 
	+ When holding down the “A” button, the clear function gets faster (generates significantly higher frame rate).
	+ When holding "Pause" button, the mode switches from 3 to 5.

3.Backgrounds

![Backgrounds GBA](https://github.com/Cabrra/cabrra.github.io/blob/master/Images/backgrounds.png)

+ The display control register is in mode 0 (value 0x0). 
+ “gfx2gba.exe” is used to convert the bitmaps to palette, image and map data. Select “External Tools->Command Prompt” and navigate to your project folder. Once there, type “gfx2gba –fsrc –m –mm –t8 –pback.pal back.bmp back1.bmp”. Read “gfx2gba-readme.txt” to learn more. 
+ Draw_PaletteInit function: copies the palette data to the appropriate palette memory address (0x05000000). 
+ Draw_BGTileInit function: sets up one background at a time. The data needs to be loaded within a 64KB chunk of memory starting at a hardware-defined offset. The copy of the tile image data needs to start at one of four 16KB "character" block offsets. The copy of the tile map data needs to start at one of thirty-two 2KB "screen" block offsets. 
+ Draw_BGScroll function: updates the scroll registers starting at memory address 0x04000010. The three backgrounds move at different velocities making a parallax effect.   
+ Controls: “LEFT”/“RIGHT” buttons move the backgrounds.
	
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