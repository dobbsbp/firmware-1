#ifndef GLOBALS_H
#define GLOBALS_H

unsigned long logTS = 0;      // TS to dump debug messages every 5 secs
unsigned long startTS = 0;    // TS for last vfd started
unsigned long reverseTS = 0;  // TS for last vfd reversing

int mode = 0;                 // see enums.h::MODE
int jamming = 0;              // jamming counter

#endif
