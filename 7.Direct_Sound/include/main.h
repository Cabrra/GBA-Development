#ifndef _MAIN_H
#define _MAIN_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "lib.def.h"
//#include "lib.dat.h"
//#include "lib.thm.h"
#include "isr.arm.h"
#include "memory.h"

//define some data type shortcuts
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef signed char s8;
typedef signed short s16;
typedef signed long s32;

extern void stopSound(void);

//my stuff

//#define REG_DMA1CNT         (*(u16*)0x40000C4)
//#define REG_SOUNDCNT_X      (*(u16*)0x04000084)
//#define REG_SOUNDCNT_H      (*(u16*)0x04000082)


#define DMA_ENABLE      0x80000000

#define R_CTRLINPUT (*(volatile u16 *)(0x4000130))
#define REG_VCOUNT *(u16*)0x04000006
#define Map_Begin ((volatile u16*)0x06000000)

#define Key_A        0x0001
#define Key_B        0x0002
#define Key_SELECT   0x0004
#define Key_START    0x0008
#define Key_RIGHT    0x0010
#define Key_LEFT     0x0020
#define Key_UP       0x0040
#define Key_DOWN     0x0080
#define Key_R        0x0100
#define Key_L        0x0200

#define Key_MASK     0x03FF


#endif
