#include "PiPuck.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include <unistd.h>

int main()
{
  while (true)
  {
  set_outer_leds(true, true, true, true, true, true, true, true);
  sleep(1);
  set_outer_leds(false, true, true, true, true, true, true, true);
  sleep(1);
  set_outer_leds(false, false, true, true, true, true, true, true);
  sleep(1);
  set_outer_leds(false, false, false, true, true, true, true, true);
  sleep(1);
  set_outer_leds(false, false, false, false, true, true, true, true);
  sleep(1);
  set_outer_leds(false, false, false, false, false, true, true, true);
  sleep(1);
  set_outer_leds(false, false, false, false, false, false, true, true);
  sleep(1);
  set_outer_leds(false, false, false, false, false, false, false, true);
  sleep(1);
  set_outer_leds(false, false, false, false, false, false, false, false);
  sleep(1);
  }

  
}