#include "main.h"

volatile int numberOfSamples = 0, samplePosition = 0;
volatile int samplesPerSecond = 8000, clocksPerSample = 0;

void MyHandler(void) {

  short isrFlags = 0;

  // service timer0
  if (REG_IF & IF_TIMER0)
  {
    if(++samplePosition >= numberOfSamples) stopSound();
    isrFlags |= IF_TIMER0;
  }

  // reset serviced interrupts
  REG_IF = isrFlags;
}
