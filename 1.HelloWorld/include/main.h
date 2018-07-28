
#ifndef _MAIN_H
#define _MAIN_H

#include <stdio.h>
#include <string.h>
#include "myFont.h"

//define some data type shortcuts
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef signed char s8;
typedef signed short s16;
typedef signed long s32;

//packs three values into a 15-bit color
#define RGB(r,g,b) ((r & 31)|((g & 31)<<5)|((b & 31)<<10))

//define some display registers
#define REG_DISPCNT *(u16*)0x4000000
#define BG2_ENABLE 0x400
#define SetMode(mode) REG_DISPCNT = (mode)
//mystuff
#define Map_Begin ((volatile u16*)0x06000000)
#define R_CTRLINPUT (*(volatile u16 *)(0x4000130))

#define F_CTRLINPUT_A_PRESSED       (~R_CTRLINPUT & 0x0001)
#define F_CTRLINPUT_B_PRESSED       (~R_CTRLINPUT & 0x0002)
#define F_CTRLINPUT_SELECT_PRESSED  (~R_CTRLINPUT & 0x0004)
#define F_CTRLINPUT_START_PRESSED   (~R_CTRLINPUT & 0x0008)

#define F_CTRLINPUT_RIGHT_PRESSED   (~R_CTRLINPUT & 0x0010)
#define F_CTRLINPUT_LEFT_PRESSED    (~R_CTRLINPUT & 0x0020)
#define F_CTRLINPUT_UP_PRESSED      (~R_CTRLINPUT & 0x0040)
#define F_CTRLINPUT_DOWN_PRESSED    (~R_CTRLINPUT & 0x0080)

#define F_CTRLINPUT_R_PRESSED       (~R_CTRLINPUT & 0x0100)
#define F_CTRLINPUT_L_PRESSED       (~R_CTRLINPUT & 0x0200)


//define some interrupt registers
#define REG_IME        *(u16*)0x4000208
#define REG_IE         *(u16*)0x4000200
#define REG_IF         *(u16*)0x4000202
#define REG_INTERRUPT  *(u32*)0x3007FFC

#define REG_DISPSTAT   ((*(u16*)0x4000004))
#define VBLANK_ENABLE 0x0008
#define HBLANK_ENABLE 0x0010
#define VCOUNT_ENABLE 0x0020
#define VCOUNT_trigger (((count) & 0xFF) << 8)
#define Set_DisplayState(my_value) REG_DISPSTAT = (my_value)

//define some interrupt constants
#define INT_VBLANK 0x0001
#define INT_HBLANK 0x0002
#define INT_VCOUNT 0x0004
#define INT_TIMER0 0x0008
#define INT_TIMER1 0x0010
#define INT_TIMER2 0x0020
#define INT_TIMER3 0x0040
#define INT_COM 0x0080
#define INT_DMA0 0x0100
#define INT_DMA1 0x0200
#define INT_DMA2 0x0400
#define INT_DMA3 0x0800
#define INT_BUTTON 0x1000
#define INT_CART 0x2000

//define the timer constants
#define TIMER_FREQUENCY_SYSTEM 0x0
#define TIMER_FREQUENCY_64 0x1
#define TIMER_FREQUENCY_256 0x2
#define TIMER_FREQUENCY_1024 0x3
#define TIMER_OVERFLOW 0x4
#define TIMER_ENABLE 0x80
#define TIMER_IRQ_ENABLE 0x40

//define the timer status addresses
#define REG_TM0CNT     *(volatile u16*)0x4000102
#define REG_TM1CNT     *(volatile u16*)0x4000106
#define REG_TM2CNT     *(volatile u16*)0x400010A
#define REG_TM3CNT     *(volatile u16*)0x400010E

//define the timer data addresses
#define REG_TM0D       *(volatile u16*)0x4000100
#define REG_TM1D       *(volatile u16*)0x4000104
#define REG_TM2D       *(volatile u16*)0x4000108
#define REG_TM3D       *(volatile u16*)0x400010C

//define some video mode values
#define MODE_3 0x3
#define BG2_ENABLE 0x400

//my functions

static inline void DrawPixel3(int x, int y, unsigned short c)
{
     Map_Begin[y * 240 + x] = c;
}

static inline void DrawLetter(int left, int top, char letter, u16 color)
{
    int x, y;
    int draw;
    
    for(y = 0; y < 8; y++)
    {
         for (x = 0; x < 8; x++)
         {
             draw = g_ucFont[(letter-32) * 64 + y * 8 + x];

            if (draw)
            DrawPixel3(left + x, top + y, color);
        }
    }
}

//crazy stuff
u16 __key_curr=0, __key_prev=0;

#define KEY_A        0x0001
#define KEY_B        0x0002
#define KEY_SELECT   0x0004
#define KEY_START    0x0008
#define KEY_RIGHT    0x0010
#define KEY_LEFT     0x0020
#define KEY_UP       0x0040
#define KEY_DOWN     0x0080
#define KEY_R        0x0100
#define KEY_L        0x0200

#define KEY_MASK     0x03FF

// Polling function
void key_poll()
{
    __key_prev= __key_curr;
    __key_curr= ~R_CTRLINPUT & KEY_MASK;
}

// Key is being hit (down now, but not before).
u32 key_hit(u32 key)
{   return ( __key_curr &~ __key_prev) & key;  }

#endif

