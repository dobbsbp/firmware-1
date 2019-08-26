#ifndef ALARM_H
#define ALARM_H

void alarm() {
  tone(ALARM_SOUND_PIN, 4000, 500);
}

#endif
