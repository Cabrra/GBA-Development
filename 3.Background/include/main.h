
#ifndef _MAIN_H
#define _MAIN_H

#include <stdio.h>
#include <string.h>
#include "headers.h"
#include "memory.h"

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
#define MODE_0 0x0
#define MODE_3 0x3
#define BG2_ENABLE 0x400

//my stuff
#define R_CTRLINPUT (*(volatile u16 *)(0x4000130))
//crazy stuff
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

#define pallete         ((u16*)0x5000000)

#define BGstorage0      ((u16*)0x6000000)
#define BGstorage1      ((u16*)0x6008000)
#define BGstorage3      ((u16*)0x600C000)

#define REG_BG0        (*(u16*)0x4000008)
#define REG_BG1        (*(u16*)0x400000A)
#define REG_BG2        (*(u16*)0x400000C)
#define REG_BG3        (*(u16*)0x400000E)

#define REG_MAP0         ((u16*) 0x600F000)
#define REG_MAP1         ((u16*) 0x600E000)
#define REG_MAP2         ((u16*) 0x600D800)

#define BG0_ENABLE 0x100
#define BG1_ENABLE 0x200
#define BG2_ENABLE 0x400
#define BG3_ENABLE 0x800

#define REG_VCOUNT *(u16*)0x04000006

//X and Y
#define REG_BG0X       (*(u16*)0x4000010)// - REG_BG0HOFS Horizontal scroll co-ordinate for BG0 (Write Only)
#define REG_BG0Y       (*(u16*)0x4000012) // - REG_BG0VOFS Vertical scroll co-ordinate for BG0 (Write Only)
#define REG_BG1X       (*(u16*)0x4000014) //- REG_BG1HOFS Horizontal scroll co-ordinate for BG1 (Write Only)
#define REG_BG1Y       (*(u16*)0x4000016) // - REG_BG1VOFS Vertical scroll co-ordinate for BG1 (Write Only)
#define REG_BG2X       (*(u16*)0x4000018) //- REG_BG2HOFS Horizontal scroll co-ordinate for BG2 (Write Only)
#define REG_BG2Y       (*(u16*)0x400001A) //- REG_BG2VOFS Vertical scroll co-ordinate for BG2 (Write Only)
#define REG_BG3X       (*(u16*)0x400001C) // - REG_BG3HOFS Horizontal scroll co-ordinate for BG3 (Write Only)
#define REG_BG3Y       (*(u16*)0x400001E) // - REG_BG3VOFS Vertical scroll co-ordinate for BG3 (Write Only)

static void Draw_PaletteInit()
{
    Memory_DMAFastCopy((void*)pallete, (void*)back_Palette, 128,DF_COPY_32);
    pallete[255] = 0x7FFF;
}

static void Draw_BGTileInit()
{
    //bg0
    Memory_DMAFastCopy((void*)BGstorage0 , (void*)back_Tiles, 8128,DF_COPY_32);
    //map0
    Memory_DMAFastCopy((void*)REG_MAP0 , (void*)back_Map, 1024, DF_COPY_32);
    REG_BG0 = (30<<8) | (1<<14) | (1 << 7);
    //bg1
     Memory_DMAFastCopy((void*)BGstorage1 , (void*)back1_Tiles, 4064, DF_COPY_32);
    //map1
    Memory_DMAFastCopy((void*)REG_MAP1 , (void*)back1_Map, 1024, DF_COPY_32);
    REG_BG1 = (28<<8) | (2 << 2) | (1 << 7);

    //map2
   REG_BG2 = (30<<8) | (1<<14) | (1 << 7);
   
   //star
    Memory_DMAFastCopy((void*)BGstorage3 , (void*)Star_Tiles, 96, DF_COPY_32);
    REG_BG3 = (27<<8) | (3 << 2) | (1 << 7) | (3);
    
    REG_MAP2[65] = 0;
}

static void WaitVBlank()
{
    // non-reentrant (using bit flag)	OR THIS ONE
   //while (!(REG_DISPSTAT & DISPSTAT_VFRESH));
   // while (REG_DISPSTAT & DISPSTAT_VFRESH);

    while(REG_VCOUNT >= 160);
    while(REG_VCOUNT < 160);
}
#endif

