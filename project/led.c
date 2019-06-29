// Adrian Gomez Rodriguez
// Computer Architecture 1
// T-Th 7:30-8:50
// Prof. Dr. Freudenthal
// TA. Daniel Cervantes 

#include <msp430.h>
#include "led.h"
#include "switches.h" 

void led_init(){
  P1DIR |= LEDS;	
}

int setLed(int ledRedState, int ledGreenState){ 
  if(ledRedState < 0 || ledRedState > 1 || ledGreenState < 0 || ledRedState > 1)
    return 0;   
  
  char ledFlags = 0; /* by default, no LEDs on */
  ledFlags |= ledRedState ? LED_RED : 0;  //from button_demo 
  ledFlags |= ledGreenState ? LED_GREEN : 0; //from button_demo 
  
  P1OUT &= (0xff - LEDS) | ledFlags;
  P1OUT |= ledFlags;
}  

void led_update(){    
}
