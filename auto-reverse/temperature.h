#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#ifdef HAS_TEMPERTURE
 #include <max6675.h>
#endif
MAX6675 ktc(TEMPERTURE_SCK_PIN, TEMPERTURE_CS_PIN, TEMPERTURE_SO_PIN);

int temperature = 0;
unsigned long temperature_TS = 0;

void temperature_loop() {

  if (millis() - temperature_TS > TEMPERTURE_INTERVAL) {
    temperature_TS = millis();
    temperature = ktc.readCelsius();
  }
}

bool temperatureOk() {
  return temperature < TEMPERTURE_MAX;
}
#endif
