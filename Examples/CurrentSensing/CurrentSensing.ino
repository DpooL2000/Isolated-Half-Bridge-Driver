#include <HalfBridgeDriver.h>

// We connect the AD8418 output (J4) to Arduino analog pin A0
HalfBridgeDriver motor(A0);

void setup() {
    Serial.begin(115200);
    
    motor.begin();
    
    Serial.println("Driver initialized. Starting motor at 50% duty cycle...");
    motor.setDutyCycle(50.0);
}

void loop() {
    // Read the actual current passing through the R002 shunt
    float amps = motor.readCurrentAmps();
    
    Serial.print("Motor Current (A): ");
    Serial.println(amps, 3); // Print with 3 decimal places for precision
    
    // Simple software over-current protection (e.g., trip at 10 Amps)
    if (amps > 10.0 || amps < -10.0) {
        motor.emergencyStop();
        Serial.println("FAULT: Over-current detected! Driver halted.");
        while(true); // Freeze the program
    }
    
    delay(100); 
}