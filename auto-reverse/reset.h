#ifndef RESET_H
#define RESET_H

int isReset = 0;
void reset_setup() {}

void reset_loop() {
  isReset = digitalRead(RESET_PIN);
}



#endif
