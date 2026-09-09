#ifndef HALF_BRIDGE_DRIVER_H
#define HALF_BRIDGE_DRIVER_H

#include <Arduino.h>

// Architecture Guards
#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
    #define SAFE_PWM_H 9
    #define SAFE_PWM_L 10
#elif defined(ARDUINO_ARCH_STM32)
    // STM32 target pins depend on the specific series (e.g., F1 vs G4)
    #define SAFE_PWM_H PA8 // TIM1_CH1
    #define SAFE_PWM_L PA7 // TIM1_CH1N
#else
    #error "DANGER: Architecture not supported! Complementary PWM with deadtime is not implemented for this board."
#endif

class HalfBridgeDriver {
public:
    HalfBridgeDriver(uint8_t currentSensePin);
    
    void begin();
    void setDutyCycle(float percent);
    void emergencyStop();
    float readCurrentAmps();

private:
    uint8_t _sensePin;
    const float _vRef = 1.65;
    const float _shuntResistor = 0.002;
    const float _ampGain = 20.0;
};

#endif