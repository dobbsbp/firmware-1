#ifndef PROXIMITY_H
#define PROXIMITY_H

//  Typical proximity switch. This needs debouncing.
//  Wiring :
//    Blue  -> GND
//    Brown -> 6 - 36 V
//    Black -> Digital In (PROXIMITY_INPUT)

#include <Bounce2.h>
#include "config.h"

unsigned long SENSOR_HIGH_TS = 0;   // Last HIGH TS
unsigned long SENSOR_LOW_TS = 0;    // Last LOW TS
unsigned long SENSOR_DT = 0;        // Last delta time between HIGH / LOW
unsigned long now = 0;              // Temp. variable to store tick TS

int moving = 0;                     // Final result
int proxValue = 0;                  // Temp. variable to track sensor value, for debugging

Bounce proxDebouncer = Bounce();

void proximity_setup()
{

  now = millis();
  SENSOR_HIGH_TS = now;
  SENSOR_DT = now;

  proxDebouncer.attach(PROXIMITY_INPUT, INPUT_PULLUP);
  proxDebouncer.interval(25);

  moving = 0;
}

void proximity_reset()
{

  now = millis();
  SENSOR_HIGH_TS = now;
  SENSOR_DT = now;
  moving = 0;
}

void proximity_loop()
{

  proxDebouncer.update();
  proxValue = proxDebouncer.read() ? LOW : HIGH;

  now = millis();
  if (proxValue == HIGH)
  {
    SENSOR_HIGH_TS = now;
  }
  else
  {
    SENSOR_LOW_TS = now;
  }

  if (SENSOR_HIGH_TS <= SENSOR_LOW_TS)
  {
    SENSOR_DT = SENSOR_LOW_TS - SENSOR_HIGH_TS;
  }
  else
  {
    SENSOR_DT = SENSOR_HIGH_TS - SENSOR_LOW_TS;
  }

  SENSOR_DT = abs(SENSOR_DT);

  if (SENSOR_DT > PROXIMITY_TIMEOUT)
  {
    moving = 0;
  }
  else
  {
    moving = 1;
  }
}

#endif
