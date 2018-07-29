Pixel Manipulation
==================

## Overview

![Hello World GBA](https://github.com/Cabrra/cabrra.github.io/blob/master/Images/hello_world.png)

1. Hello World & buffered input
+ Unsigned short pointer to memory address 0x04000000: this is the display control register bit flags are located. Flags: 0x3 for mode 3 and 0x400 for background 2. 
+ Unsigned short pointer to memory address 0x06000000: it points to the beginning of the pixel map which will be displayed on the screen. Each pixel is represented by a 16-bit number for a 15-bit color value. 
+ Volatile unsigned short pointer to memory address 0x04000130: it is volatile because the hardware changes these bits. Used to check the button states. 
+ Controls: �UP�/�DOWN�/�LEFT�/�RIGHT�/"L"/"R"/"START"/"SELECT" enables/disables the letters.

![Bitmaps GBA](https://github.com/Cabrra/cabrra.github.io/blob/master/Images/bitmaps.png)

2.Bitmaps
+ Mode 3 and background 2. Memory allocated in EWRAM (EXRAM) for the back buffer.
+ Draw_Clear function: clears the back buffer to a particular color in a for loop. 
+ Draw_Pixel function: Plots a pixel anywhere on the back buffer (used to draw the bitmap). 
+ Draw_WaitVBlank function: Waits until the beginning of the vertical blank period.
+ Draw_Present function: copies the entire back buffer to the front buffer during vblank to avoid visual artifacts.
+ Screen is set to a different color every frame; starting with color=0, and then it increments by +8 on every frame. 
+ Controls: 
	+ When holding down the �DOWN� button, the present function gets faster (no screen artifacts because is presented fast enough during vertical blank). 
	+ When holding down the �A� button, the clear function gets faster (generates significantly higher frame rate).
	+ When holding "Pause" button, the mode switches from 3 to 5.

![Backgrounds GBA](https://github.com/Cabrra/cabrra.github.io/blob/master/Images/backgrounds.png)

3.Backgrounds
+ The display control register is in mode 0 (value 0x0). 
+ �gfx2gba.exe� is used to convert the bitmaps to palette, image and map data. Select �External Tools->Command Prompt� and navigate to your project folder. Once there, type �gfx2gba �fsrc �m �mm �t8 �pback.pal back.bmp back1.bmp�. Read �gfx2gba-readme.txt� to learn more. 
+ Draw_PaletteInit function: copies the palette data to the appropriate palette memory address (0x05000000). 
+ Draw_BGTileInit function: sets up one background at a time. The data needs to be loaded within a 64KB chunk of memory starting at a hardware-defined offset. The copy of the tile image data needs to start at one of four 16KB "character" block offsets. The copy of the tile map data needs to start at one of thirty-two 2KB "screen" block offsets. 
+ Draw_BGScroll function: updates the scroll registers starting at memory address 0x04000010. The three backgrounds move at different velocities making a parallax effect.   
+ Controls: �LEFT�/�RIGHT� buttons move the backgrounds.

![Fireball GBA](https://github.com/Cabrra/cabrra.github.io/blob/master/Images/fireball.png)

4.Fireball
+ OR-ing the display control register with 0x40 sets the 1D sprite image data flag. OR-ing 0x1000 to set the OAM memory enable flag.
+ Implemented a method to DMA the raw sprite palette data into sprite palette video memory area located at 0x05000200.  
+ Implemented a method to DMA the raw sprite tile data into sprite tile video memory area located at 0x06010000.
+ Implemented a method to DMA the OAM memory buffer to OAM video memory area located at 0x7000000. This function is called during program initialization and on every frame during the v-blank period.
+ Implemented a method to change the sprite X and Y position in the OAM memory buffer. This should be updating attributes 0 and 1 of the sprite�s data.
+ Implemented a method to calculate and set the rotational and scaling data  (PA, PB, PC, PD) of a rotational instance within the OAM memory buffer.
+ OAM memory buffer controls the sprite's rotational data.
+ OAM memory buffer is initialized with all sprites disabled (setting all attribute bits to zero). 
+ Sprite #0 is initialized with rotation enabled and double sized, 256 color palette options.
+ Sprite�s scale is set to 1<<8, the degree to 0, and the X and Y translation values to 0 (These variables are controlled by key input).
+ Controls: �UP�/�DOWN�/�LEFT�/�RIGHT� buttons translates the sprite. �L�/�R� rotates the sprite. �L�/�R� will scale the sprite. "A"/"B" adds alpha channel. �START� button resets the sprite.

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