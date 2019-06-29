// Adrian Gomez Rodriguez
// Computer Architecture 1
// T-Th 7:30-8:50
// Prof. Dr. Freudenthal
// TA. Daniel Cervantes 
 
#ifndef timer_included
#define timer_included

/* LCG constants */
#define M 49381 // Multiplier
#define I 8643 // Increment

void statrTimer();
void timer_set_state_transition(unsigned short delay);
unsigned short lapsed();
unsigned int prand();

#endif 
