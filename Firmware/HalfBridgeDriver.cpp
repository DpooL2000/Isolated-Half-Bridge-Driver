#include "HalfBridgeDriver.h"
#include "hw_timers.h"

HalfBridgeDriver::HalfBridgeDriver(uint8_t currentSensePin) {
    _sensePin = currentSensePin;
}

void HalfBridgeDriver::begin() {
    // 1. Fail-safe: Force outputs LOW before timer takes over
    pinMode(SAFE_PWM_H, OUTPUT);
    pinMode(SAFE_PWM_L, OUTPUT);
    digitalWrite(SAFE_PWM_H, LOW);
    digitalWrite(SAFE_PWM_L, LOW);

    // 2. Attach the hardware timer
    hw_timer_init();
}

void HalfBridgeDriver::setDutyCycle(float percent) {
    if (percent < 0.0) percent = 0.0;
    
    // Clamp to 95% max duty cycle to allow the bootstrap capacitor to recharge
    if (percent > 95.0) percent = 95.0; 
    
    hw_pwm_update(percent);
}

void HalfBridgeDriver::emergencyStop() {
    hw_force_low();
}

float HalfBridgeDriver::readCurrentAmps() {
    int raw = analogRead(_sensePin);
    
    // Convert 10-bit ADC raw value to voltage (Assuming 3.3V reference)
    float voltage = (raw / 1023.0) * 3.3; 
    
    // Calculate actual current: I = (Vout - Vref) / (Gain * Rshunt)
    float current = (voltage - _vRef) / (_ampGain * _shuntResistor);
    
    return current;
}