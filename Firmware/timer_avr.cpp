#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)

#include "hw_timers.h"

// Set TOP to 400. At 16MHz, Phase Correct PWM, this yields exactly 20kHz switching frequency.
const uint16_t TIMER_TOP = 400; 
const uint16_t DEADTIME_TICKS = 6; // Approx 375 nanoseconds of deadtime

void hw_timer_init() {
    // Stop Timer1
    TCCR1A = 0;
    TCCR1B = 0;

    // Set Phase and Frequency Correct PWM, Mode 8 (TOP = ICR1)
    TCCR1B |= (1 << WGM13);

    // Channel A (Pin 9) - Non-inverting (Clear on up-count, Set on down-count)
    TCCR1A |= (1 << COM1A1);
    
    // Channel B (Pin 10) - Inverting (Set on up-count, Clear on down-count)
    TCCR1A |= (1 << COM1B1) | (1 << COM1B0);

    ICR1 = TIMER_TOP;
    
    // Start with 0% duty cycle safely
    OCR1A = 0;
    OCR1B = TIMER_TOP; 

    // Start timer with no prescaler (16MHz)
    TCCR1B |= (1 << CS10);
}

void hw_pwm_update(float percent) {
    uint16_t dutyTicks = (uint16_t)((percent / 100.0) * TIMER_TOP);
    
    // Apply deadtime logic via register offset
    OCR1A = dutyTicks;
    
    // Prevent underflow/overflow on the offset channel
    if (dutyTicks + DEADTIME_TICKS > TIMER_TOP) {
        OCR1B = TIMER_TOP;
    } else {
        OCR1B = dutyTicks + DEADTIME_TICKS;
    }
}

void hw_force_low() {
    TCCR1A = 0; // Detach timer from pins immediately
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
}

#endif