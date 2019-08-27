#ifndef HALL_H
#define HALL_H

int minCurrent = 0;     //this is the current value that the machine uses to recognise when it is spinning, but not shredding.
int hall_value = 0;
unsigned long hall_TS = 0;


void hall_reset();

void hall_setup() {
  pinMode(HALL_PIN, INPUT);
  hall_reset();
}

void hall_loop() {
  if (millis() - hall_TS > HALL_INTERVAL) {
    hall_TS = millis();
    hall_value = analogRead(HALL_PIN);
  }
}

void hall_reset() {
  hall_TS = millis();
  hall_value = 0 ;
}

bool hallOk() {
  return hall_value <= MAX_AMPS;
}



#endif
