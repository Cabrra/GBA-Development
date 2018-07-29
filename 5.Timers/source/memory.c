// All things memory
// JJM 051027

#include "memory.h"

// DEFINES

// Registers for using DMA3 source, destination, and control
#define REG_DMA3SAD *(volatile unsigned int*)0x040000D4
#define REG_DMA3DAD *(volatile unsigned int*)0x040000D8
#define REG_DMA3CNT *(volatile unsigned int*)0x040000DC
#define DMA_ENABLE  0x80000000

// IMPLEMENTATION

void Memory_DMAFastCopy(void* pvDest, const void* pvSource, unsigned int unCount, unsigned int unMode)
{
    // make sure unCount is not zero or else DMA will do very bad things to memory!!!
    //if(unCount)
    //{
        // clear out the DMA control bits or else DMA will yet again do very bad things
        // to memory next time you use it!!!
        REG_DMA3CNT = 0;

        REG_DMA3DAD = (unsigned int)pvDest;
        REG_DMA3SAD = (unsigned int)pvSource;
        REG_DMA3CNT |= unCount | unMode | DMA_ENABLE;
    //}
}
