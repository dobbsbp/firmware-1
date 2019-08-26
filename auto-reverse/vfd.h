#include "config.h"
#include "enums.h"

void rev(bool on);
void fwd(bool on);

int vfd_dir = 0;

void stop();

void vfd_setup()
{
  pinMode(FWD_PIN, OUTPUT);
  pinMode(REV_PIN, OUTPUT);
  stop();
}

void fwd(bool on)
{
  if (on)
  {
    rev(false);
    vfd_dir = DIRECTION::FORWARD;
  }
  else
  {
    vfd_dir = DIRECTION::STOP;
  }
  analogWrite(FWD_PIN, on ? RELAY_ON : RELAY_OFF);
}

void rev(bool on)
{
  if (on)
  {
    fwd(false);
    vfd_dir = DIRECTION::REVERSE;
  }
  else
  {
    vfd_dir = DIRECTION::STOP;
  }
  analogWrite(REV_PIN, on ? RELAY_ON : RELAY_OFF);
}

void stop()
{
  rev(false);
  fwd(false);
  vfd_dir = DIRECTION::STOP;
}
