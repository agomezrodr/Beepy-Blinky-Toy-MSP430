// Adrian Gomez Rodriguez
// Computer Architecture 1
// T-Th 7:30-8:50
// Prof. Dr. Freudenthal
// TA. Daniel Cervantes 

#ifndef switches_included  
#define switches_included 

#define BOTTOM1 BIT3 // p1.3
#define BOTTOM_BUTTONS BOTTOM1

#define TOP1 BIT0 // p2.0
#define TOP2 BIT1 // p2.1
#define TOP3 BIT2 // p2.2
#define TOP4 BIT3 // p2.3
#define TOP_BUTTONS (TOP1 | TOP2 | TOP3 | TOP4)

void switch_init();   
void switch_interrupt_handler(); 

extern char b1Bottom;
extern char b1Top;
extern char b2Top;
extern char b3Top;
extern char b4Top;

#endif // included
