Subcircuit Documentation
1. Optocoupler Isolation Stage
This section safely isolates the low-voltage control logic from the high-voltage motor drive circuitry, preventing transient spikes from damaging the microcontroller.

The circuit utilizes two 6N137 high-speed optocouplers (U11 and U4) to provide galvanic isolation for the incoming PWM signals.

Control signals enter through a 2-pin screw terminal (J3) and pass through 330Ω current-limiting resistors (R1, R2) to drive the internal LEDs of the optocouplers.

The secondary side of the optocouplers is powered by a 5V rail, decoupled by 0.1uF capacitors (C14, C13).

The open-drain outputs are pulled up to the 3.3V logic rail via 1kΩ resistors (R3, R4), resulting in the isolated CH and CNH control signals.
