#ifndef STATUS_H
#define STATUS_H

void status_setup() { }

void setStatus(bool error) {
  if (error) {
    analogWrite(STATUS_ERROR_PIN, RELAY_ON);
    analogWrite(STATUS_OK_PIN, RELAY_OFF);
  } else {
    analogWrite(STATUS_OK_PIN, RELAY_ON);
    analogWrite(STATUS_ERROR_PIN, RELAY_OFF);
  }
}

#endif
