#include "PiPuck.h"

#include <sys/ioctl.h>
#include <time.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <signal.h>

void sigintHandler(int sig_num)
{
  set_motor_speeds(0, 0);
  enable_ir_sensors(false);
  set_inner_leds(false, false);
  set_outer_leds_byte(0);
  exit(0);
}

int main()
{
  signal(SIGINT, sigintHandler);
  const int MAX_SPEED = 500;
  float delay = 0.1;
  write_data_8(0x00, 0x00);
  struct timespec ts;
  ts.tv_sec = 0;
  ts.tv_nsec = 100000;

  int weights_left[8] = {-10, -10, -5, 0, 0, 5, 10, 10};
  int weights_right[8] = {10, 10, 5, 0, 0, -5, -10, -10};
  char ir_led_mapping[8] = {0x01, 0x02, 0x04, 0x18, 0x30, 0x40, 0x80, 0x01};
  
  enable_ir_sensors(true);
  u_int16_t ir[8];
  int left, right;
  int leds_on = 0;

  while (true)
  {
    memset(ir, 0, sizeof(ir)/sizeof(*ir));

    for (int index = 0; index < 8; index++)
    {
      ir[index] = get_ir_reflected(index);
    }

    left = right = MAX_SPEED / 2;

    for (int index = 0; index < 8; index++)
    {
      if (ir[index] > 300)
      {
        leds_on |= ir_led_mapping[index];
        left += weights_left[index]* ir[index];
        right += weights_right[index] * ir[index];
      }
    }
    set_outer_leds_byte(leds_on);

    if (leds_on == 0)
    {
      set_inner_leds(true, false);
    }
    else
    {
      set_inner_leds(false, true);
    }

    if (left > MAX_SPEED)
    {
      left = MAX_SPEED;
    }
    else if (left < -MAX_SPEED)
    {
      left = -MAX_SPEED;
    }

    if (right > MAX_SPEED)
    {
      right = MAX_SPEED;
    }
    else if (right < -MAX_SPEED)
    {
      right = -MAX_SPEED;
    }

    set_motor_speeds(left, right);
    nanosleep(&ts, &ts);
  }
}
