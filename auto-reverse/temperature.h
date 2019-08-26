#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#ifdef HAS_TEMPERTURE
#include <max6675.h>

MAX6675 ktc(TEMPERTURE_SCK_PIN, TEMPERTURE_CS_PIN, TEMPERTURE_SO);

int temperature = 0;
unsigned long temperature_TS = 0;
void temperatur_setup() {
  temperature_TS = millis();
}

void temperature_loop() {

  if (millis() - temperature_TS > TEMPERTURE_INTERVAL) {
    temperature_TS = millis();
    temperature = ktc.readCelsius();
    Serial.println(temperature);
  }
}


#endif


#endif
