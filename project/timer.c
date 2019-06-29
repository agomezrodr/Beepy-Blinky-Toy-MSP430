// Adrian Gomez Rodriguez
// Computer Architecture 1
// T-Th 7:30-8:50
// Prof. Dr. Freudenthal
// TA. Daniel Cervantes 

#include <msp430.h>
#include "timer.h"
#include "stateMachine.h"

static unsigned int randDelay = 0;

static unsigned short startTime = 0;
static unsigned short presentTime = 0;

static unsigned short stateTime = 0;
static unsigned short stateTrans = 0;

void statrTimer(){
  startTime = presentTime;
}

unsigned short lapsed(){
  randDelay += presentTime % 5;
  return presentTime - startTime;
}

void __interrupt_vec(WDT_VECTOR) WDT(){
  stateTime++;
  presentTime++;
  randDelay++;
  
  if(stateTime >= stateTrans){
    stateTime = 0;
    randDelay += 5;
    buttonUpdate();
  }
}

void timer_set_state_transition(unsigned short delay){
  stateTrans = delay;
}

unsigned int prand() {
  return M * randDelay + I;                     // Generate the next state of the LCG
} 
