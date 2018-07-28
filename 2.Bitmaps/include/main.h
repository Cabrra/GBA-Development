
#ifndef _MAIN_H
#define _MAIN_H

#include <stdio.h>
#include <string.h>
#include <MrAtari.h>
#include <memory.h>

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
#define REG_DISPCNT (*(volatile u16*)0x4000000)
#define BG2_ENABLE 0x400
#define SetMode(mode) REG_DISPCNT = (mode)

//mystuff
extern volatile u16 *myPointer;
extern int mode;

#define Map_Begin ((volatile u16*)0x06000000) //screen = backbuffer

#define BackBuffer1 ((volatile u16*)0x6000000)// mode5
#define BackBuffer2 ((volatile u16*)0x600A000)// mode5

#define R_CTRLINPUT (*(volatile u16 *)(0x4000130))
#define free_map ((volatile u16*)0x02000000) // second backbuffer
//end in 240*160*2 bites (76800)
#define REG_VCOUNT *(u16*)0x04000006
#define backdrop (unsigned short*) 0x05000000

#define vid_page     ((volatile u16*)Map_Begin)
#define BACKBUFFER    0x0010
#define VID_FLIP     0x0000a000


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
#define

 0x3
#define BG2_ENABLE 0x400

//my functions

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

static inline void DrawPixel3(int x, int y, unsigned short c)//, int mode)
{
    if (mode == 3)
        free_map[y * 240 + x] = c;
    else
        myPointer[y * 160 + x] = c;
}

static inline void DrawBitmap(int left, int top) //, int mode)
{
    int x, y;

    for(y = 0; y < 64; y++)
    {
         for (x = 0; x < 64; x++)
         {
            DrawPixel3(left + x, top + y, misteratari_Bitmap[x+y*64]); //, mode);
        }
    }
}

static void Draw_Init()
{
     SetMode(0x3 | BG2_ENABLE);
}

static void Draw_Clear(u16 color) //, int mode)
{
    int x, y;
    
    if (mode == 3)
    {
        for(y = 0; y < 160; y++)
        {
            for (x = 0; x < 240; x++)
            {
                DrawPixel3(x, y, color); //, mode);
            }
        }
    }
    else
    {
           for(y = 0; y < 128; y++)
        {
            for (x = 0; x < 160; x++)
            {
                DrawPixel3(x, y, color); //, mode);
            }
        }
    }
}

static void Draw_WaitVBlank()
{
    // non-reentrant (using bit flag)	OR THIS ONE
   //while (!(REG_DISPSTAT & DISPSTAT_VFRESH));
   // while (REG_DISPSTAT & DISPSTAT_VFRESH);
   
    while(REG_VCOUNT >= 160);
    while(REG_VCOUNT < 160);
}

static void Draw_Present()
{
     int x, y;

    for(y = 0; y < 160; y++)
    {
         for (x = 0; x < 240; x++)
         {
           Map_Begin[y * 240 + x] = free_map[y * 240 + x];
        }
    }
}

static void Draw_Present_DMA()
{

    Memory_DMAFastCopy((void*)Map_Begin, (void*)free_map, 38400, DF_COPY_16);
}

static void Draw_Clear_DMA(u16 color)
{
    if (mode==3)
        memset((void*)free_map, color, 76800);
    else
        memset((void*)myPointer, color, 40960);
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

