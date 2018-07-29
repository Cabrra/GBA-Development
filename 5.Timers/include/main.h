
#ifndef _MAIN_H
#define _MAIN_H

#include <stdio.h>
#include <string.h>
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
#define IWRAM_CODE	__attribute__((section(".iwram"), long_call))

#define REG_WSCNT           (*(u16*) 0x4000204)

#define R_CTRLINPUT (*(volatile u16 *)(0x4000130))

#define pallete         ((u16*)0x5000000)
#define BG0Storage      ((u16*)0x6000000)
#define REG_BG0         (*(u16*)0x4000008)
#define REG_MAP0        ((u16*) 0x600F000)

#define REG_VCOUNT *(u16*)0x04000006

#endif

