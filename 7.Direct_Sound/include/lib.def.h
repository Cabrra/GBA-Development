#ifndef _LIBDEF_H
#define _LIBDEF_H

#define TRUE 1
#define FALSE 0
#define FOREVER TRUE

// bit definitions
#define BIT0 (0x0001 << 0)
#define BIT1 (0x0001 << 1)
#define BIT2 (0x0001 << 2)
#define BIT3 (0x0001 << 3)
#define BIT4 (0x0001 << 4)
#define BIT5 (0x0001 << 5)
#define BIT6 (0x0001 << 6)
#define BIT7 (0x0001 << 7)
#define BIT8 (0x0001 << 8)
#define BIT9 (0x0001 << 9)
#define BIT10 (0x0001 << 10)
#define BIT11 (0x0001 << 11)
#define BIT12 (0x0001 << 12)
#define BIT13 (0x0001 << 13)
#define BIT14 (0x0001 << 14)
#define BIT15 (0x0001 << 15)
#define BIT16 (0x0001 << 16)
#define BIT17 (0x0001 << 17)
#define BIT18 (0x0001 << 18)
#define BIT19 (0x0001 << 19)
#define BIT20 (0x0001 << 20)
#define BIT21 (0x0001 << 21)
#define BIT22 (0x0001 << 22)
#define BIT23 (0x0001 << 23)
#define BIT24 (0x0001 << 24)
#define BIT25 (0x0001 << 25)
#define BIT26 (0x0001 << 26)
#define BIT27 (0x0001 << 27)
#define BIT28 (0x0001 << 28)
#define BIT29 (0x0001 << 29)
#define BIT30 (0x0001 << 30)
#define BIT31 (0x0001 << 31)

#define REG_DISPCNT (*(volatile unsigned short *) 0x04000000)

  #define DISPCNT_VM0 0x00
  #define DISPCNT_VM1 0x01
  #define DISPCNT_VM2 0x02
  #define DISPCNT_VM3 0x03
  #define DISPCNT_VM4 0x04
  #define DISPCNT_VM5 0x05
  #define DISPCNT_VM6 0x06
  #define DISPCNT_VMX (BIT0|BIT1|BIT2)
  #define DISPCNT_FLIP BIT4
  #define DISPCNT_HBLANK_PROC BIT5
  #define DISPCNT_1D BIT6
  #define DISPCNT_BLANK BIT7
  #define DISPCNT_BG0 BIT8
  #define DISPCNT_BG1 BIT9
  #define DISPCNT_BG2 BIT10
  #define DISPCNT_BG3 BIT11
  #define DISPCNT_BGX_MASK (BIT8|BIT9|BIT10|BIT11)
  #define DISPCNT_OAM BIT12
  #define DISPCNT_WIN0 BIT13
  #define DISPCNT_WIN1 BIT14
  #define DISPCNT_WINX_MASK (BIT13|BIT14)
  #define DISPCNT_WIN BIT15

#define IRQ_VECTOR (*(unsigned long *) 0x03007FFC)
#define REG_SOUNDCNT_L (*(volatile unsigned short*)0x4000080)
#define REG_SOUNDCNT_H (*(volatile unsigned short*)0x4000082)
#define SOUNDCNT_H_A_RIGHT_CHANNEL  BIT8
#define SOUNDCNT_H_A_LEFT_CHANNEL   BIT9
#define SOUNDCNT_H_A_FIFO_RESET     BIT15
#define REG_SOUNDCNT_X (*(volatile unsigned short*)0x4000084)
#define SOUNDCNT_X_MASTER_ENABLE    128

#define REG_FIFOA (*(volatile unsigned long*) 0x040000A0)

#define REG_DMA1CNT (*(volatile unsigned long *) 0x040000C4)

  #define DMAXCNT_DSTDEC BIT21
  #define DMAXCNT_DSTCONST BIT22
  #define DMAXCNT_SRCDEC BIT23
  #define DMAXCNT_SRCCONST BIT24
  #define DMAXCNT_REPEAT BIT25
  #define DMAXCNT_COPY32 BIT26
  #define DMAXCNT_VBLANK BIT28
  #define DMAXCNT_HBLANK BIT29
  #define DMAXCNT_FIFO (DMAXCNT_VBLANK|DMAXCNT_HBLANK)
  #define DMAXCNT_INTERRUPT BIT30
  #define DMAXCNT_ENABLE BIT31
  #define DMAXCNT_16NOW (DMAXCNT_ENABLE)
  #define DMAXCNT_32NOW (DMAXCNT_ENABLE|DMAXCNT_COPY32)
  #define DMAXCNT_16VBL (DMAXCNT_ENABLE|DMAXCNT_VBLANK)
  #define DMAXCNT_32VBL (DMAXCNT_ENABLE|DMAXCNT_VBLANK|DMAXCNT_COPY32)

#define REG_TM0D (*(volatile unsigned short *) 0x04000100)
#define REG_TM0CNT (*(volatile unsigned short *) 0x04000102)

  #define TMXCNT_TICK1      0
  #define TMXCNT_TICK64     BIT0
  #define TMXCNT_TICK256    BIT1
  #define TMXCNT_TICK1024   BIT0|BIT1
  #define TMXCNT_CASCADE    BIT2
  #define TMXCNT_OVERFLOW   BIT3
  #define TMXCNT_INTERRUPT  BIT6
  #define TMXCNT_ENABLE     BIT7
  #define TMXCNT_DISABLE    0

  #define CLKOSC 16777216   // clock oscillator frequency

#define  REG_KEY (*(volatile unsigned short *) 0x04000130)

  #define KEY_A       BIT0
  #define KEY_B       BIT1
  #define KEY_SELECT  BIT2
  #define KEY_START   BIT3
  #define KEY_RIGHT   BIT4
  #define KEY_LEFT    BIT5
  #define KEY_UP      BIT6
  #define KEY_DOWN    BIT7
  #define KEY_R       BIT8
  #define KEY_L       BIT9
  #define KEY_MASK    (KEY_A|KEY_B|KEY_SELECT|KEY_START|KEY_RIGHT|KEY_LEFT|KEY_UP|KEY_DOWN|KEY_R|KEY_L)

  #define WIN_Z       KEY_A
  #define WIN_X       KEY_B
  #define WIN_BACKSPACE KEY_SELECT
  #define WIN_ENTER   KEY_START
  #define WIN_RIGHT   KEY_RIGHT
  #define WIN_LEFT    KEY_LEFT
  #define WIN_UP      KEY_UP
  #define WIN_DOWN    KEY_DOWN
  #define WIN_S       KEY_R
  #define WIN_A       KEY_L
  #define WIN_MASK    (WIN_Z|WIN_X|WIN_BACKSPACE|WIN_ENTER|WIN_RIGHT|WIN_LEFT|WIN_UP|WIN_DOWN|WIN_S|WIN_A)

#define REG_IE (*(volatile unsigned short *) 0x04000200)

  #define IE_TIMER0   BIT3

#define REG_IF (*(volatile unsigned short *) 0x04000202)

  #define IF_TIMER0   BIT3

#define REG_IME (*(volatile unsigned short *) 0x04000208)

  #define IME_DISABLE 0
  #define IME_ENABLE BIT0

#define COLOR_OFF 0x00
#define COLOR_ON 0x1F
#define RGB(r,g,b) (((r) & 31)|(((g) & 31)<<5)|(((b) & 31)<<10))

#define BLACK RGB(COLOR_OFF, COLOR_OFF, COLOR_OFF)
#define WHITE RGB(COLOR_ON, COLOR_ON, COLOR_ON)
#define RED RGB(COLOR_ON, COLOR_OFF, COLOR_OFF)
#define YELLOW RGB(COLOR_ON, COLOR_ON, COLOR_OFF)
#define MAGENTA RGB(COLOR_ON, COLOR_OFF, COLOR_ON)
#define GREEN RGB(COLOR_OFF, COLOR_ON, COLOR_OFF)
#define CYAN RGB(COLOR_OFF, COLOR_ON, COLOR_ON)
#define BLUE RGB(COLOR_OFF, COLOR_OFF, COLOR_ON)
#define BROWN RGB(13, 8, 3)

#define RGB_MODFLG BIT15              // color modifier mask
#define RGB_BOXRND (RGB_MODFLG|BIT14) // randomize box color
#define RGB_BITRND (RGB_MODFLG|BIT13) // randomize bit color
#define RGB_CHRRND (RGB_MODFLG|BIT12) // randomize character color
#define RGB_STRRND (RGB_MODFLG|BIT11) // randomize string color

#endif
