#include "config.h"
#include "globals.h"
#include "vfd.h"
#include "proximity.h"
#include "switch.h"
#include "auto-reverse.h"


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

  #ifdef STATUS
    status_setup();
  #endif

  #ifdef HAS_RESET
    reset_setup();
  #endif

}

void loop() {

  if(HAS_AUTO_REVERSE){
    auto_reverse_loop();
    return;
  }

  switch_loop();
  
  #ifdef HAS_STATUS
    setStatus(false);
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
        last_switch = STOP;
        break;
      }
  }
  delay(100);
}
