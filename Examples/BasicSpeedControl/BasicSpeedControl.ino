#include <HalfBridgeDriver.h>

// Initialize the driver and pass the analog pin used for current sensing
// (Even if we aren't using current sensing in this example, the class needs the pin)
HalfBridgeDriver motor(A0);

void setup() {
    // The begin() function automatically forces pins low and configures the hardware timers
    motor.begin();
    
    // Optional: wait a moment before starting
    delay(2000);
}

void loop() {
    // Ramp up the motor from 0% to 80%
    for (float duty = 0.0; duty <= 80.0; duty += 1.0) {
        motor.setDutyCycle(duty);
        delay(50);
    }
    
    // Hold speed
    delay(2000);
    
    // Ramp down smoothly
    for (float duty = 80.0; duty >= 0.0; duty -= 1.0) {
        motor.setDutyCycle(duty);
        delay(50);
    }
    
    // Safety stop and wait before repeating
    motor.emergencyStop();
    delay(3000);
    
    // Re-initialize the timer if you want to start again after an emergency stop
    motor.begin(); 
}