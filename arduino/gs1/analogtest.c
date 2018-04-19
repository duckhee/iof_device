#define ANALOGTEST_LOCAL

#include "analogtest.h"

ANALOGTESET_DEF int get_value(int pin);

int value = 0;

ANALOGTESET_DEF int get_value(int pin)
{
  value = analogRead(pin);

  return value;
}

