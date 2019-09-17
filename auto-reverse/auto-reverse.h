#ifndef AUTO_REVERSE_H
#define AUTO_REVERSE_H

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

#ifdef HAS_STATUS
  #include "status.h"
#endif

#ifdef HAS_RESET
  #include "reset.h"
#endif

#ifdef HAS_RESET
  void resetSys(){  
    stop();
  }
#endif

void onFatal() {

  #ifdef ALARM_SOUND
    alarm();
  #endif

  #ifdef HAS_STATUS
    setStatus(true);
  #endif
}


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


void auto_reverse_loop() {

  #ifdef HAS_PROXIMITY
    proximity_loop();
  #endif

  #ifdef HAS_HALL
    hall_loop();
  #endif
  
  #ifdef HAS_STATUS
    setStatus(false);
  #endif

  #ifdef HAS_RESET
    reset_loop();
    if(isReset){
      resetSys();
      delay(1000);
      return;
    }
  #endif

  #ifdef HAS_TEMPERTURE
    temperature_loop();
    if (!temperatureOk()) {
      mode = FATAL;
      onFatal();
      return;
    }
  #endif
  
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
        #ifdef HAS_PROXIMTY
          proximity_reset();
        #endif
        return;
      } else {
        jamming = 0;
      }
    }

    if (mode == JAMMING) {
      if (jamming >= MAX_REVERSE_TRIALS) {
        mode = FATAL;
        stop();
        
        #ifdef HAS_PROXIMTY
              moving = false;
        #endif
        
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
#endif
