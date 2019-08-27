#include "config.h"
#include "vfd.h"
#include "proximity.h"
#include "switch.h"


#ifdef HAS_TEMPERTURE
#include "temperature.h"
#endif

#ifdef ALARM_SOUND
#include "alarm.h"
#endif

#ifdef HAS_HALL
#include "hall.h"
#endif

#ifdef HAS_PROXIMITY
#include "proximity.h"
#endif


unsigned long logTS = 0;      // TS to dump debug messages every 5 secs

unsigned long startTS = 0;    // TS for last vfd started
unsigned long reverseTS = 0;  // TS for last vfd reversing

int mode = 0;                 // see enums.h::MODE
int jamming = 0;              // jamming counter


// our main 'is shredding function', utilizing different sensors
bool isShredding() {

  bool ret = true;

#ifdef HAS_PROXIMITY
  if (!proximityOk()) {
    return false;
  }
#endif

#ifdef HAS_HALL
  ret = hallOk();
#endif

  return ret;
}


void setup() {
  if (DEBUG) {
    Serial.begin(19200);
  }

  vfd_setup();
  switch_setup();
  logTS = millis();

#ifdef HAS_PROXIMTY
  proximity_setup();
#endif

#ifdef HAS_HALL
  hall_setup();
#endif

}

void onFatal() {

#ifdef ALARM_SOUND
  alarm();
#endif

}

void loop() {

  switch_loop();
  proximity_loop();

#ifdef HAS_HALL
  hall_loop();
#endif


#ifdef HAS_TEMPERTURE
  temperature_loop();
  if (!temperatureOk()) {
    mode = FATAL;
    onFatal();
    return;
  }
#endif


  if (DEBUG) {
    if (millis() - logTS > DEBUG_INTERVAL) {
      logTS = millis();
      char data[124];
      sprintf(data, "DEBUG 3POS : %d || MOVING : %d || VFD : %d || last dir switch : %d | mode = %d | sensor = %lu | jamming=%d" , switch_pos, moving, vfd_dir, last_switch, mode, SENSOR_DT, jamming);
      Serial.println(data);
    }
  }



  if (switch_pos == FORWARD) {

    if (last_switch == STOP) {
      if (!isShredding() && mode == HALT) {
        startTS = millis();
        mode = STARTING;
      }
    }

    if (mode == STARTING) {
      if (millis() - startTS > STARTING_TIMEOUT) {
        if (isShredding()) {
          mode = SHREDDING;
        } else {
          mode = JAMMING;
          stop();
          return;
        }
      }
    }

    if (mode == SHREDDING) {
      if (!isShredding()) {
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
        onFatal();
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

#ifdef HAS_PROXIMTY
        moving = false;
#endif

      }
    }
  }

#ifdef ALARM_SOUND
  if (mode == FATAL) {
    alarm();
  }
#endif

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
