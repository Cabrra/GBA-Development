GBA Development
===============

## Overview

![Hello World GBA](https://raw.githubusercontent.com/Cabrra/cabrra.github.io/master/Images/hello_world.png?token=AI_RbesgbD_eb6ApIngqA__Bg8jirQj7ks5bo5sPwA%3D%3D)

### 1. Hello World & buffered input
+ Unsigned short pointer to memory address 0x04000000: this is the display control register bit flags are located. Flags: 0x3 for mode 3 and 0x400 for background 2. 
+ Unsigned short pointer to memory address 0x06000000: it points to the beginning of the pixel map which will be displayed on the screen. Each pixel is represented by a 16-bit number for a 15-bit color value. 
+ Volatile unsigned short pointer to memory address 0x04000130: it is volatile because the hardware changes these bits. Used to check the button states. 
+ Controls: 
	+ “UP”/“DOWN”/“LEFT”/“RIGHT”/"L"/"R"/"START"/"SELECT" enables/disables the letters.


![Bitmaps GBA](https://raw.githubusercontent.com/Cabrra/cabrra.github.io/master/Images/bitmaps.png?token=AI_RbbG6B0VGvK2d_Vfnh1xrXvxqlgP2ks5bo5sSwA%3D%3D)

### 2.Bitmaps
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

	
![Backgrounds GBA](https://raw.githubusercontent.com/Cabrra/cabrra.github.io/master/Images/backgrounds.png?token=AI_RbcyxH0IIHVJmAWazNOvYatshEuupks5bo5sUwA%3D%3D)

### 3.Backgrounds
+ The display control register is in mode 0 (value 0x0). 
+ “gfx2gba.exe” is used to convert the bitmaps to palette, image and map data. Select “External Tools->Command Prompt” and navigate to your project folder. Once there, type “gfx2gba –fsrc –m –mm –t8 –pback.pal back.bmp back1.bmp”. Read “gfx2gba-readme.txt” to learn more. 
+ Draw_PaletteInit function: copies the palette data to the appropriate palette memory address (0x05000000). 
+ Draw_BGTileInit function: sets up one background at a time. The data needs to be loaded within a 64KB chunk of memory starting at a hardware-defined offset. The copy of the tile image data needs to start at one of four 16KB "character" block offsets. The copy of the tile map data needs to start at one of thirty-two 2KB "screen" block offsets. 
+ Draw_BGScroll function: updates the scroll registers starting at memory address 0x04000010. The three backgrounds move at different velocities making a parallax effect.   
+ Controls: 
	+ “LEFT”/“RIGHT” buttons move the backgrounds.


![Fireball GBA](htthttps://raw.githubusercontent.com/Cabrra/cabrra.github.io/master/Images/fireball.png?token=AI_RbfSUDRYWv1AicdLD73xRT9hiFWwgks5bo5sWwA%3D%3D)

### 4.Fireball
+ OR-ing the display control register with 0x40 sets the 1D sprite image data flag. OR-ing 0x1000 to set the OAM memory enable flag.
+ Implemented a method to DMA the raw sprite palette data into sprite palette video memory area located at 0x05000200.  
+ Implemented a method to DMA the raw sprite tile data into sprite tile video memory area located at 0x06010000.
+ Implemented a method to DMA the OAM memory buffer to OAM video memory area located at 0x7000000. This function is called during program initialization and on every frame during the v-blank period.
+ Implemented a method to change the sprite X and Y position in the OAM memory buffer. This should be updating attributes 0 and 1 of the sprite’s data.
+ Implemented a method to calculate and set the rotational and scaling data  (PA, PB, PC, PD) of a rotational instance within the OAM memory buffer.
+ OAM memory buffer controls the sprite's rotational data.
+ OAM memory buffer is initialized with all sprites disabled (setting all attribute bits to zero). 
+ Sprite #0 is initialized with rotation enabled and double sized, 256 color palette options.
+ Sprite’s scale is set to 1<<8, the degree to 0, and the X and Y translation values to 0 (These variables are controlled by key input).
+ Controls: 
	+ “UP”/“DOWN”/“LEFT”/“RIGHT” 		buttons translates the sprite. 
	+ “L”/“R” 							rotates the sprite. 
	+ "A" 								adds alpha channel
	+ "B" 								adds a mosaic effect. 
	+ “START” 							button resets the sprite.
	+ While the “SELECT” button is held down pressing “L”/“R” to scales the sprite.
	
	
![Timers GBA](https://raw.githubusercontent.com/Cabrra/cabrra.github.io/master/Images/timers.png?token=AI_RbTauWWCfNiBiIXcVJprtHFn3CDqGks5bo5sXwA%3D%3D)
	
### 5.Timers and Interrupts
+ Video mode is set to mode 0 and background 0 (BG0).
+ Interrupt service routine is defined on file named "isr.arm.c" to count the number of vertical blank interrupts and number of seconds that have elapsed since starting the program. The counter parameters are global and volatile in order to be share between the main() the ISR.
+ Implemented string print() method to set the appropriate character font tile index into the appropriate position in the tile map.
+ The SECONDS and FPS counters only are updated to the video screen once a second in order to minimize the work being done by the main() executive loop.
+ Controls:
	+ WaitVBlank() is called when the "A" button IS NOT pressed.
	+ WaitVBlank() when the "DOWN" button IS pressed and held down.
	+ Results are: WaitVBlank() is called once when both buttons are NOT pressed, or both buttons ARE pressed; WaitVBlank() is not called at all when only the 'A' button is pressed;  WaitVBlank() is called twice when only the 'DOWN' button is pressed.  Pressing these keys will affect both the FRAMES and FPS counter.
	+ Note: it is possible to obtain 600,000+ FPS with optimizer set to -o0, and 2,000,000+ FPS with the optimizer set to -o2. But I didn't set those flags.

	
![Tile Mode GBA](https://raw.githubusercontent.com/Cabrra/cabrra.github.io/master/Images/tile_mode.png?token=AI_Rbc13z5GnGJ-36uDW7GLUCHASr7Wgks5bo5sZwA%3D%3D)	
	
### 6.Tile Mode
+ Video mode set to 2 and background enabled 2
+ Draw_PaletteInit function: loads the palette into memory. 
+ Draw_BGTileInit function: sets up the control register for background 2 and load the tile image and tile map data provided. The control register is set to a standard 256 color palette, with a rotational background size 128x128 (16x16 tiles), and the wrap around (screen over) bit set.
+ Math_M2Identity, Math_M2Identity_FP_24_8, and Math_M2Identity_FP_16_16 functions: These functions take in a 2D matrix and convert it into an identity matrix. One is fixed point 24.8 (24 bits for the signed bit and integer and 8 bits for the fraction) and another is fixed point 16.16. So for every value set in the matrix, is bit shifted it to the left by 8 and 16 respectively. 
+ Math_M2TranslationSet function: takes in a translation data and set it to a matrix.
+ Math_M2ScaleSet_FP_24_8 function: takes in fixed point 24.8 scaling data and set it to a matrix. This function create a matrix that is of fixed point 24.8 format (allowing more range for scale values).
+ Math_M2RotationSet_FP_16_16 function: takes in rotation data and set it to a matrix. Creates a matrix that is of fixed point 16.16 format (allowing more precision for the fractional rotation).
+ Math_M2Mult function is used to calculate a resulting matrix. Multiplying in the following order: rotation, then scale, and lastly translation.
+ Write a Draw_BGTransformation function that will copy the matrix data into the six transformation registers for background 2 like so: 
+ Controls:
	+ “UP”/“DOWN”/“LEFT”/“RIGHT” 	buttons translate the background. 
	+ “A”/“B” 						scale the background. 
	+ “L”/“R” 						rotate the background. 
	+ “START” 						resets the background.
	

![Sound GBA](https://raw.githubusercontent.com/Cabrra/cabrra.github.io/master/Images/direct_sound.png?token=AI_RbQWgkNWE1NkaAQ51sw2v44cDpwzvks5bo5sawA%3D%3D)

### 7.Direct Sound
+ "wav2gba.exe" To generate the ‘C’ audio data file, use the following on the cmd: 
	> "wav2gba  yourSoundTrackName.wav  yourSoundTracName.c  yourSoundTrackName"
+ Controls:
	+ "R": 		stops playing sound
	+ "L": 		starts or restarts playing sound
	+ "START": 	sets samplesPerSecond to 8000
	+ "UP": 	adds 1000 to samplesPerSecond
	+ "DOWN": 	subtracts 1000 from samplesPerSecond
KEY_RIGHT pressed – adds 100 to samplesPerSecond
KEY_LEFT pressed – subtracts 100 from samplesPerSecond


![Numbers GBA](https://raw.githubusercontent.com/Cabrra/cabrra.github.io/master/Images/numbers.png?token=AI_RbW8j-lswm8Tknb6be2_VSLbZ4c6Iks5bo5scwA%3D%3D)

### 8.Numbers
+ This folder contains a visual representation of the Signed Magnitude, One’s Compliment and Two’s Compliment numbers. Displaying on the GBA screen in binary form the integer values -128 to +127 for the three number formats, each with a different random color scheme.
+ Controls:
	+ "UP"/"DOWN":			+10/-10 to value.
	+ "LEFT"/"RIGHT":		+1/-1 to value.

	
![Ninja GBA](https://raw.githubusercontent.com/Cabrra/cabrra.github.io/master/Images/rain_ninja.png?token=AI_RbZ4ts7GuUSQ0DvZVrrlJKiNFFkDQks5bo5sgwA%3D%3D)

### 9.Ninja project: applying all together
+ This small project applies some of the learnings from previous projects.
+ The sprite tile image data is loaded only once into video memory. 
+ The animation is generated changing the sprite data’s tile index. 
+ The sprite uses the 1st frame for standing, and when input is held down.
+ The sprite is flipped horizontally based on the direction it is running in.
+ Controls:
	+ "LEFT"/"RIGHT":		move the ninja left/right and rotate the rain.

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
* Richard E. Arndt
