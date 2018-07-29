// All things memory
// JJM 051027

#include "memory.h"

// DEFINES

// Registers for using DMA3 source, destination, and control
//#define REG_DMA3SAD *(volatile unsigned int*)0x040000D4
//#define REG_DMA3DAD *(volatile unsigned int*)0x040000D8
//#define REG_DMA3CNT *(volatile unsigned int*)0x040000DC
#define DMA_ENABLE  0x80000000

#define REG_DMA1CNT     (*(volatile unsigned int*)0x40000C4)
#define REG_DMA1SAD     (*(volatile unsigned int*)0x40000BC)
#define REG_DMA1DAD     (*(volatile unsigned int*)0x40000C0)

// IMPLEMENTATION

void Memory_DMAFastCopy(void* pvDest, const void* pvSource, unsigned int unCount, unsigned int unMode)
{
        REG_DMA1CNT = 0;

        REG_DMA1DAD = (unsigned int)pvDest;
        REG_DMA1SAD = (unsigned int)pvSource;
        REG_DMA1CNT |= unCount | unMode | DMA_ENABLE;
}
