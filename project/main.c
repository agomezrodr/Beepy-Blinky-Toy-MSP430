// Adrian Gomez Rodriguez
// Computer Architecture 1
// T-Th 7:30-8:50
// Prof. Dr. Freudenthal
// TA. Daniel Cervantes 


#include <msp430.h>
#include "stateMachine.h" 
#include "led.h"
#include "switches.h"  
#include "buzzer.h"

void main(void) {
  switch_init();  
  configureClocks();
  buzzer_init();
  led_init();
  setLed(1, 1);  
  enableWDTInterrupts();
  or_sr(0x18);
} 
