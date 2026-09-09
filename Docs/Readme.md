# Subcircuit Documentation

## 1. Optocoupler Isolation Stage
This section safely isolates the low-voltage control logic from the high-voltage motor drive circuitry, preventing transient spikes from damaging the microcontroller.

<img width="749" height="549" alt="image" src="https://github.com/user-attachments/assets/f0de0289-745c-4e40-9552-c014d31445f0" />

* The circuit utilizes two 6N137 high-speed optocouplers (U11 and U4) to provide galvanic isolation for the incoming PWM signals.
* Control signals enter through a 2-pin screw terminal (J3) and pass through 330Ω current-limiting resistors (R1, R2) to drive the internal LEDs of the optocouplers.
* The secondary side of the optocouplers is powered by a 5V rail, decoupled by 0.1uF capacitors (C14, C13).
* The open-drain outputs are pulled up to the 3.3V logic rail via 1kΩ resistors (R3, R4), resulting in the isolated `CH` and `CNH` control signals.

## 2. Power Supply & Voltage Reference
This stage regulates the main battery voltage into clean logic levels and generates a stable center-bias voltage for bidirectional current sensing.

<img width="760" height="647" alt="image" src="https://github.com/user-attachments/assets/7418f2a1-c89a-4857-96d7-f737e5e7009f" />

* The main battery voltage (`+BATT`) from screw terminal J1 is stepped down to 5V by an AMS1117-5.0 linear regulator (U6).
* A second regulator, an AMS1117-3.3 (U5), steps the voltage down further to provide a 3.3V rail for logic-level pull-ups and amplifier supply.
* Standard 10uF and 0.1uF capacitors are utilized on the regulator inputs and outputs for stability and transient suppression.
* A precise 1.65V reference voltage is generated using a 50% voltage divider consisting of two 10kΩ resistors (R5, R6) connected across the 3.3V rail. 
* This divider is buffered by an LMH6611 operational amplifier (U2) configured as a unity-gain follower, providing a low-impedance 1.65V source.

## 3. Half-Bridge & Bootstrap Driver
This high-power switching stage translates the isolated logic signals into the high current required to drive the motor.

<img width="794" height="510" alt="image" src="https://github.com/user-attachments/assets/f556b5bb-f055-4402-b00e-1f4ab2561902" />

* An IR2101 high/low-side driver IC (U8) manages the switching of two IRFZ44N N-channel power MOSFETs (Q1, Q2) configured in a half-bridge topology.
* Because an N-channel MOSFET on the high side requires a gate voltage higher than the main battery rail (`+BATT`), a bootstrap circuit is implemented using a 1N5819 Schottky diode (D3) and a 1uF capacitor (C3).
* The isolated control signals `CH` and `CNH` are pulled up to 5V via 1kΩ resistors (R8, R7) before feeding into the driver IC.
* The driver outputs connect to the MOSFET gates through 22Ω resistors (R13, R14) to dampen ringing and limit peak switching current.
* A 1000uF bulk electrolytic capacitor (C10) sits across the high-voltage rail and ground to smooth out heavy current demands from the motor.

## 4. Current Sensing & Analog Filtering
This circuit measures the physical output current of the half-bridge and translates it into a clean, center-biased analog voltage.

<img width="790" height="524" alt="image" src="https://github.com/user-attachments/assets/db884823-df0b-4fa6-9d00-af4158da1eed" />

* Motor current flows through an R002 (2mΩ) inline shunt resistor (R19), creating a small voltage drop proportional to the current.
* An AD8418 high-resolution current sense amplifier (U1) measures this differential voltage.
* To reject high-frequency switching noise, the inputs to the amplifier are heavily filtered using 10Ω resistors (R25, R26), a 10nF differential capacitor (C19), and 1nF common-mode capacitors (C27, C26).
* The amplifier's reference pins (REF1 and REF2) are tied to the buffered 1.65V rail. This center-biases the output, allowing the microcontroller to read both forward and reverse motor currents.
* The final analog output passes through an RC low-pass filter (330Ω R9 and 100nF C11) before exiting via the `current analog reading` connector (J4).
