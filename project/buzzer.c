// Adrian Gomez Rodriguez
// Computer Architecture 1
// T-Th 7:30-8:50
// Prof. Dr. Freudenthal
// TA. Daniel Cervantes 

#include <msp430.h>
#include "led.h" 
#include "buzzer.h"
#include "musicNotes.h" 

static int song[] = {700, 3000, 700, 3000, 700, 30000, 700, 3000,
		     700, 3000, 700, 3000, 700, 3000, 700, 3000, 700, 3000, 
		     700, 3000, 700, 3000, 700, 3000, 700, 3000, 700, 3000,
		     700, 3000, 700, 3000, 700, 3000, 700, 3000, 700, 3000, 
		     700, 3000, 700, 3000, 700, 0, 0, 0, -1};
//N1, N2, N3, N4, N5, N6, N7, N8, N9, N10,
 // N11, N12, N13, N14, N15, N16, N17, N18, N19, N20,
 //N21, N22, N23, N24, N25, N26, N27, N28, N29, N30,
//N31, N32, N34, N35, N36, N37, N38, N39, N40, N41, N42};

static int tone[] = {1200, 0, -1};
//300, 700, 1200, 700, 3000, 700, 300, 700, 700, 130, 310, 8, 310, 310, 310,
// 8, 10, 8, 5, 8, 8, 8, 8, 10, 10, 10, 10, 8, 10, 10, 10, 8,
//5, 10, 8 ,5, 8, 8, 8, 8};

static unsigned short quarter_duration = 300;
static unsigned short presentNote = 0;
static unsigned short time = 0;
char state = 0;


void buzzer_init(){
  timerAUpmode();		
  P2SEL2 &= ~(BIT6 | BIT7);
  P2SEL &= ~BIT7; 
  P2SEL |= BIT6;
  P2DIR |= BIT6;	
  
  time = (int)(quarter_duration / tone[0]); 
  state = buzzerReady;               
  presentNote = 0;               
}
void buzzer_play(){
  state = playBuzzer;  
  // Get the present note from the song
  int note = song[presentNote]; 
  
  // Check if the song is done
  if(note < 0){ 
    state = buzzerReady;  
    presentNote = 0;             
    return;    
  }
  if(note == 0){
    setLed(1, 0); //red on, green off
  }
  
  else{
    setLed(0, 1);  //red off, green on
  }
  // Play the current note
  buzzer_set_period(note);             
  time++;
  
  if(time <= 1){
    presentNote--;
    // Update the note time
    time = (int)(quarter_duration / tone[presentNote]);
  }  
}                         
void buzzer_set_period(short cycles)
{ 
  CCR0 = cycles; 
  CCR1 = cycles >> 1;		/* one half cycle */
}
