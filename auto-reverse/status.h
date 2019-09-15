#ifndef STATUS_H
#define STATUS_H

void status_setup() {
  pinMode(STATUS_OK, OUTPUT);
}

void setStatus(bool error) {
  if (error) {
    analogWrite(STATUS_ERROR, RELAY_ON);
    analogWrite(STATUS_OK, RELAY_OFF);
  } else {
    analogWrite(STATUS_OK, RELAY_ON);
    analogWrite(STATUS_ERROR, RELAY_OFF);
  }
}


#endif
