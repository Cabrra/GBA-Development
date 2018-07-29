
#ifndef _MAIN_H
#define _MAIN_H

#include <stdio.h>
#include <string.h>
#include "fireball.h"
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
#define MODE_3 0x3
#define BG2_ENABLE 0x400

//my stuff
typedef struct _OAMSPR {
    u16 attr0, attr1, attr2, fill3;
} OAMSPR;

OAMSPR oamspr[128];

typedef struct _OAMROT {
  s16 filla[3], pa, fillb[3], pb, fillc[3], pc, filld[3], pd;
} OAMROT;

OAMROT *oamrot = (OAMROT *) oamspr;



#define MODE_0      0x0
#define OAMMEM      0x1000
#define IDSprite    0x40

extern const int g_nCos_FP_16_16[360];
extern const int g_nSin_FP_16_16[360];
extern const u16 FireballData[];
extern const u16 FireballPalette[];

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

#define REG_VCOUNT *(u16*)0x04000006

#define pallete    ((u16*)0x5000200)
#define fireBall    ((u16*)0x06010000)
#define OAMVideo    ((u16*)0x7000000)
#define backdrop    (u16*) 0x05000000
#define ATTR1_X_MASK		0x01FF
#define ATTR0_Y_MASK		0x00FF
#define REG_BLDMOD     *(u16*)0x4000050 //blending
#define REG_MOSAIC     *(u32*)0x400004C //Mosaic
#define REG_COLEV      *(u16*)0x4000052 //coeficient

static void WaitVBlank()
{
    while(REG_VCOUNT >= 160);
    while(REG_VCOUNT < 160);
}

static void Draw_PaletteInit()
{
    Memory_DMAFastCopy((void*)pallete, (void*)FireballPalette, 128, DF_COPY_32);
}

static void Draw_DataInit()
{
    Memory_DMAFastCopy((void*)fireBall, (void*)FireballData, 128, DF_COPY_32);
}

static void OAMMemInit()
{
     memset((void*)oamspr, 0x0000, sizeof(oamspr[0]) *128);
     int i;
     for(i = 1; i <128; i++)
        oamspr[i].attr0 |= (1<<9);
        
    // 16x32 = 1010
    oamspr[0].attr0 |= (1<<8) | (1<<9) | (1<<13) |(2<<14) | (2<<15) | (1 << 10) | (1 << 12);
    
    oamspr[0].attr1 |= (2<<14) | (2<<15);
  //  oamspr[0].attr2 = 0;
  
    REG_BLDMOD = 0x0000;
    REG_BLDMOD |= (1 <<7) | (1 << 13) | (1 << 4);
}

static void DMAtoOAM()
{
    
     Memory_DMAFastCopy((void*)OAMVideo, (void*)oamspr, sizeof(oamspr[0])*128/4, DF_COPY_32);
     (*backdrop) = RGB(13,8,3);
}

static void OAMTranslate(int xPos, int yPos)
{
    oamspr[0].attr1 &= ~ATTR1_X_MASK;
    oamspr[0].attr1 |= (xPos & ATTR1_X_MASK);

    oamspr[0].attr0 &= ~ATTR0_Y_MASK;
    oamspr[0].attr0 |= (yPos & ATTR0_Y_MASK);
}

static void OAMRotate(int scale, int degree)
{
    oamrot[0].pa = (scale * (g_nCos_FP_16_16[degree]>>8)) >> 8;
    oamrot[0].pb = (scale * (g_nSin_FP_16_16[degree]>>8)) >> 8;
    oamrot[0].pc = (scale * -(g_nSin_FP_16_16[degree]>>8)) >> 8;
    oamrot[0].pd = (scale * (g_nCos_FP_16_16[degree]>>8)) >> 8;
}

static void UpdateMosaic(u8 bh, u8 bv, u8 oh, u8 ov)
{
    REG_MOSAIC= bh + (bv<<4) + (oh<<8) + (ov<<12);
}

static void Blending(u16 top, u16 bottom)
{
    REG_COLEV = (top & 0x3f) | (bottom << 8); //| 0x2;
}

#endif

