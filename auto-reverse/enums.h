#ifndef ENUMS_H
#define ENUMS_H



enum DIRECTION : unsigned char
{
  FORWARD = 1,
  STOP = 0,
  REVERSE = 2
};

enum MODE : unsigned char
{
  HALT = 0,
  STARTING = 1,
  SHREDDING = 2,
  BREAKING = 3,
  REVERSING = 4,
  JAMMING = 5,
  FATAL = 6
};

#endif
