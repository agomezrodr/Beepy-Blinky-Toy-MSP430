
// Adrian Gomez Rodriguez
// Computer Architecture 1
// T-Th 7:30-8:50
// Prof. Dr. Freudenthal
// TA. Daniel Cervantes 


#include <msp430.h>
#include "timer.h"
#include "stateMachine.h"
#include "buzzer.h"
#include "led.h"
#include "switches.h"

#define REACTION_TIME 50

// State transitions
static enum {begin, stateOne, stateTwo, playGame, startLed}
  presentState = begin;
// The delay for the LED game
static short setDelay = 0;

// External buzzer state
char buzzerState;

void buttonUpdate(){
  switch (presentState){
  case begin:
    // Begin the music
    buzzer_play();
    if(buzzerState == buzzerReady)  //if-statement that let me convine music and blinking leds
      presentState = stateOne;
    if(b1Top || b2Top || b3Top || b4Top || b1Bottom){
      presentState = stateOne;       // go to case stateOne
      buzzerState = buzzerReady;
      buzzer_set_period(0);
    }
    break;
    
    //case that led green led blink
  case stateOne:
    timer_set_state_transition(150);  // time for blinking
    // Flash green
    setLed(0, 1);
    presentState = stateTwo;
    break;
    
    //case that led red led blink and check to which state is going
  case stateTwo:
    // Flash red
    setLed(1, 0);
    if(b1Top)
      presentState = playGame;
    else if(b2Top)
      presentState = startLed;
    else
      presentState = stateOne;
    break;
    
    //case that play music
  case playGame:
    // Reset the timer
    timer_set_state_transition(0);
    // Turn off the lights
    setLed(0,0);
    // Check if we want to go back to the state one
    if(b1Bottom){
      presentState = stateOne;
      break;
    }
    
    //Set frequency for buttons 1 to 4
    short period = 0;
    if(b1Top)
      period = 300;
    
    if(b2Top)
      period = 1020;
    
    if(b3Top)
      period = 700;
    
    if(b4Top)
      period = 3800;
    
    buzzer_set_period(period);
    setLed(period != 0, period == 0);
    
    break;
    
    // case statement that let me make the transition from music to top buttons with out any error.
  case startLed:
    // Start the game by default
    setLed(0,0);
    buzzer_set_period(0);
    // Select a random delay for pressing
    setDelay = (short)(prand () % 20) + 50;
    statrTimer();
    timer_set_state_transition(25);
    break;
  }
}  

