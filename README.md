# Isolated Half-Bridge Motor Driver

A robust, single half-bridge motor driver featuring galvanic PWM isolation and high-resolution bidirectional current sensing. Designed to safely interface a microcontroller with high-voltage motor rails while providing precise analog current feedback.

## Project Status
- **Hardware:** Complete (KiCad schematic and PCB layout finalized).
- **Firmware:** C++ driver code currently in development.

## Key Hardware Specifications
* **Gate Driver:** IR2101 with bootstrap topology (1N5819 diode / 1uF cap).
* **Power Stage:** 2x IRFZ44N N-Channel MOSFETs with 1000uF bulk smoothing.
* **Galvanic Isolation:** 2x 6N137 high-speed optocouplers protecting the logic side.
* **Current Sensing:** AD8418 bidirectional amplifier across an R002 milliohm shunt, heavily filtered (10Ω/10nF/1nF).
* **Reference Voltage:** Buffered 1.65V rail generated via MCP6002 for center-biased bidirectional sensing.

## Interface & Pinout

### Logic Side (Low Voltage)
* **PWM_H / PWM_L:** 2-Channel high-speed logic inputs (isolated via 6N137).
* **I_SENSE_OUT:** Amplified analog voltage representing motor current (centered at 1.65V).
* **VCC_LOGIC:** Input for the onboard LDO stepping down to power the opto-secondaries and IR2101.
* **GND:** Logic ground.

### Power Side (High Voltage)
* **MOTOR_V+:** Main high-voltage power rail.
* **MOTOR_OUT:** Half-bridge switching output to the motor.
* **GND_PWR:** Power ground (isolated from logic ground).

## Repository Structure
* `/Hardware` - KiCad project files (`.kicad_pro`, `.kicad_sch`, `.kicad_pcb`).
* `/Docs` - PDF schematics, board renders, and full CSV Bill of Materials.
* `/Firmware` - Placeholder for the upcoming C++ hardware abstraction and control classes. 

## Usage Notes
The design utilizes a bootstrap capacitor (C3) for the high-side MOSFET. The low-side MOSFET must be periodically pulsed on to recharge the bootstrap capacitor; do not attempt 100% duty cycle on the high side.
