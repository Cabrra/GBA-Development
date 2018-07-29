// All things memory
// JJM 051027

#ifndef _MEMORY_H_
#define _MEMORY_H_

// DMA flags for copying control (OR them together for multiple functionality)
typedef enum _DMA_FLAG  { DF_DST_INC = 0x0, DF_DST_DEC = 0x200000, DF_DST_CONST = 0x400000,
                          DF_SRC_INC = 0x0, DF_SRC_DEC = 0x800000, DF_SRC_CONST = 0x1000000,
                          DF_COPY_16 = 0x0, DF_COPY_32 = 0x4000000,
                          DF_IMM = 0x0, DF_VBLANK = 0x10000000, DF_HBLANK = 0x20000000, }
                          DMA_FLAG;

#ifdef __cplusplus
extern "C" {
#endif

// Memory_DMAFastCopy: Copy a contiguous amount of memory with hardware acceleration in
//                     immediate mode where the CPU does not process more code till the
//                     copy has completed
// pvDest   - destination address
// pvSource - source address
// unCount  - total units to copy based on the mode
// dt       - which DMA_TYPE to use
// unMode   - parameters for how to copy data
void Memory_DMAFastCopy(void* pvDest, const void* pvSource, unsigned int unCount, unsigned int unMode);

#ifdef __cplusplus
}
#endif

#endif
