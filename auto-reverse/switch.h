#ifndef POS_H
#define POS_H

#include <Bounce2.h>


// Typical 3 position switch. This needs debouncing.
// Wiring :
//  Up      -> Digital In (DIR_SWITCH_UP)
//  Down    -> Digital In (DIR_SWITCH_DOWN)
//  Middle  -> GND

int last_switch = 0;          // Track last switch position
int switch_pos = 0;           // Current switch position

int up = false;               // Temp. variable to track : up
int down = false;             // Temp. variable to track : down


Bounce debouncerUp = Bounce();
Bounce debouncerDown = Bounce();

void switch_setup()
{
  debouncerUp.attach(DIR_SWITCH_UP, INPUT_PULLUP);
  debouncerUp.interval(25);

  debouncerDown.attach(DIR_SWITCH_DOWN, INPUT_PULLUP);
  debouncerDown.interval(25);
}

void switch_loop()
{
  debouncerUp.update();
  debouncerDown.update();

  up = debouncerUp.read() == 0 ? true : false;
  down = debouncerDown.read() == 0 ? true : false;

  int newDirection = 0;

  if (up)
  {
    newDirection = FORWARD;
  }
  if (down)
  {
    newDirection = REVERSE;
  }
  if (!up && !down)
  {
    newDirection = STOP;
  }

  if (newDirection != switch_pos)
  {
    last_switch = switch_pos;
  }
  switch_pos = newDirection;
}

#endif
