 // Adrian Gomez Rodriguez
 // Computer Architecture 1
 // T-Th 7:30-8:50
 // Prof. Dr. Freudenthal
 // TA. Daniel Cervantes 

#include <msp430.h>
#include "switches.h"
#include "led.h"
#include "buzzer.h"


char b1Bottom;
char b1Top;
char b2Top;
char b3Top;
char b4Top;

// code from interrupt handler 
void __interrupt_vec(PORT1_VECTOR) Port_1(){
  if (P1IFG & BOTTOM_BUTTONS) {
    P1IFG &= ~BOTTOM_BUTTONS; // clear pendig sw interrupts
    switch_interrupt_handler(); // single handler for all switches
  }
}
// same but for green board
void __interrupt_vec(PORT2_VECTOR) Port_2(){
  if (P2IFG & TOP_BUTTONS) {
    P2IFG &= ~TOP_BUTTONS;
    switch_interrupt_handler();
  }
}

//Code given form switches form the button_demo, but adding green board.
static char switch_update_interrupt_sense_p1(){
  char p1val = P1IN;
  /* update switch interrupt sensitivity */
  P1IES |= (p1val & BOTTOM_BUTTONS);	/* if switch up, sense down */
  P1IES &= (p1val | ~BOTTOM_BUTTONS);	/* if switch down, sense up */
  return p1val;
}

static char switch_update_interrupt_sense_p2(){ //change 1 to 2's to make green board works.
  char p2val = P2IN;
  P2IES |= (p2val & TOP_BUTTONS);	/* if switch up, sense down */
  P2IES &= (p2val | ~TOP_BUTTONS);	/* if switch down, sense up */
  return p2val;
}

void switch_init(){ 
  // bottom buttons
  P1REN |= BOTTOM_BUTTONS;		/* enables resistors for switches */
  P1IE |= BOTTOM_BUTTONS;		/* enable interrupts from switches */
  P1OUT |= BOTTOM_BUTTONS;		/* pull-ups for switches */
  P1DIR |= ~BOTTOM_BUTTONS;		/* set switches' bits for input */
  switch_update_interrupt_sense_p1();
  
  // top buttons
  P2REN |= TOP_BUTTONS;		/* enables resistors for switches */
  P2IE |= TOP_BUTTONS;		/* enable interrupts from switches */
  P2OUT |= TOP_BUTTONS;		/* pull-ups for switches */
  P2DIR &= ~TOP_BUTTONS;		/* set switches' bits for input */
  switch_update_interrupt_sense_p2();
  switch_interrupt_handler();
}

void switch_interrupt_handler(){
  // Make button on the bottom works 
  char p1val = switch_update_interrupt_sense_p1();
  b1Bottom = (p1val & BOTTOM1) ? 0 : 1;
  
  // make top button works
  char p2val = switch_update_interrupt_sense_p2();
  b1Top = (p2val & TOP1) ? 0 : 1;
  b2Top = (p2val & TOP2) ? 0 : 1;
  b3Top = (p2val & TOP3) ? 0 : 1;
  b4Top = (p2val & TOP4) ? 0 : 1;
}
