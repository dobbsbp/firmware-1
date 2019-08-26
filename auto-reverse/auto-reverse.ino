#include "config.h"
#include "vfd.h"
#include "proximity.h"
#include "switch.h"

unsigned long logTS = 0;      // TS to track and dump debu messages every 5 secs

unsigned long startTS = 0;    // TS for last vfd started
unsigned long reverseTS = 0;  // TS for last vfd reversing

int mode = 0;                 // see enums.h::MODE

int jamming = 0;              // jamming counter

void setup() {
  if (DEBUG) {
    Serial.begin(19200);
  }

  vfd_setup();
  proximity_setup();
  switch_setup();

  logTS = millis();
}


void loop() {

  switch_loop();
  proximity_loop();


  if (DEBUG) {
    if (millis() - logTS > 5000) {
      logTS = millis();
      char data[100];
      sprintf(data, "DEBUG 3POS : %d || MOVING : %d || VFD : %d || last dir switch : %d | mode = %d | sensor = %lu | jamming=%d" , switch_pos, moving, vfd_dir, last_switch, mode, SENSOR_DT, jamming);
      Serial.println(data);
    }
  }

  if (switch_pos == FORWARD) {

    if (last_switch == STOP) {
      if (!moving && mode == HALT) {
        startTS = millis();
        mode = STARTING;
      }
    }

    if (mode == STARTING) {
      if (millis() - startTS > STARTING_TIMEOUT) {
        if (moving) {
          mode = SHREDDING;
        } else {
          mode = JAMMING;
          stop();
          return;
        }
      }
    }

    if (mode == SHREDDING) {
      if (!moving) {
        mode = JAMMING;
        stop();
        proximity_reset();
        return;
      } else {
        jamming = 0;
      }
    }

    if (mode == JAMMING) {
      if (jamming >= MAX_REVERSE_TRIALS) {
        mode = FATAL;
        stop();
        proximity_reset();
        return;
      }

      rev(true);
      mode = REVERSING;
      jamming++;
      reverseTS = millis();
      return;
    }

    if (mode == REVERSING) {
      if (millis() - reverseTS > REVERSING_TIMEOUT) {
        stop();
        startTS = millis();
        mode = STARTING;
        moving = false;
      }
    }
  }

  if ((mode == JAMMING || mode == FATAL || mode == REVERSING)) {
    if (switch_pos != STOP) {
      return;
    }
  }

  switch (switch_pos) {
    case FORWARD: {
        fwd(true);
        break;
      }
    case REVERSE: {
        rev(true);
        break;
      }
    case STOP: {
        stop();
        mode = HALT;
        jamming = 0;
        last_switch = STOP;
        break;
      }
  }
  delay(100);
}
