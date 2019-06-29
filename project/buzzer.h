// Adrian Gomez Rodriguez
// Computer Architecture 1
// T-Th 7:30-8:50
// Prof. Dr. Freudenthal
// TA. Daniel Cervantes 

#ifndef buzzer_included
#define buzzer_included
#define buzzerReady 0   
#define playBuzzer 1    

void buzzer_init();
void buzzer_set_period(short cycles);   
void buzzer_play();   
extern char state; 

#endif // included
