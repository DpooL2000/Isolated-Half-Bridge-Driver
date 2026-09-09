#ifndef HW_TIMERS_H
#define HW_TIMERS_H
#include <Arduino.h>

void hw_timer_init();
void hw_pwm_update(float percent);
void hw_force_low();

#endif