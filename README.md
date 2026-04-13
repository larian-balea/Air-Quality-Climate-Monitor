# Smart Indoor Air Quality & Climate Monitor

## Overview
This project is an IoT-inspired local environmental monitor designed to continuously track the air quality and humidity inside a room. Utilizing an Arduino Uno paired with environmental sensors, the system provides real-time visual and auditory feedback through a 6-LED "dashboard" and a piezo alarm. The goal is to create an immediate, intuitive warning system for poor air quality or extreme humidity levels without relying on external cloud connectivity.

## Pre-requisites
The following hardware components are required for this build:
* **Microcontroller:**
  * 1x Arduino Uno R3
* **Sensors:**
  * 1x MQ-135 Gas Sensor Module (for detecting CO2, smoke, and VOCs)
  * 1x DHT11 Temperature & Humidity Sensor Module
* **Output Indicators:**
  * 6x 5mm LEDs (2x Green, 2x Yellow, 2x Red)
  * 1x Piezo Buzzer
* **Supporting Electronics:**
  * 6x 330Ω Resistors (1/4W Metal Film)
  * 1x 400-tie point Breadboard (Half-size)
  * Assorted Male-to-Male Jumper Wires
  * 1x USB Type-A to Type-B Cable

## Schematics Plan
<img width="535" height="1025" alt="schematics" src="https://github.com/user-attachments/assets/40f20342-1fba-45c1-9b30-c259f88d83d1" />

*(Note: In the visual schematic, the MQ-135 is represented by a generic 4-pin gas sensor module proxy due to software library limitations. The wiring logic remains identical. Due to same limitations, I use a DHT11 sensor instead of the module and the wiring is the one for the module)*

### Power Distribution
* **Arduino 5V** -> Breadboard Red Power Rail `(+)`
* **Arduino GND** -> Breadboard Blue Ground Rail `(-)`

### Sensor Wiring
* **MQ-135 Gas Sensor:** VCC to `(+)`, GND to `(-)`, Analog Data to Arduino **A0**
* **DHT11 Sensor:** VCC to `(+)`, GND to `(-)`, Digital Data to Arduino **D2**

### LED Dashboard (Wired with 330Ω Resistors in series to Ground)
* **Air Quality Group:**
  * Green LED (Optimal) -> Arduino **D5**
  * Yellow LED (Warning) -> Arduino **D6**
  * Red LED (Danger) -> Arduino **D7**
* **Humidity Group:**
  * Green LED (Optimal) -> Arduino **D8**
  * Yellow LED (High/Low) -> Arduino **D9**
  * Red LED (Extreme) -> Arduino **D10**

### Alarm
* **Piezo Buzzer:** Positive terminal to Arduino **D3**, Negative terminal to Breadboard `(-)`

## Setup and Build Plan
**Phase 1: Hardware Acquisition (Done)**
- [x] Gather all necessary microcontrollers, sensors, and passive components.
- [x] Verify component compatibility (5V logic for MQ-135, logic limits for LEDs).

**Phase 2: Prototyping & Wiring (Done)**
- [x] Establish 5V and GND power rails on the breadboard.
- [x] Wire the 6-LED dashboard using compact vertical resistor placement.
- [x] Connect and mount the MQ-135 and DHT11 sensors.
- [x] Document the physical layout in CircuitCanvas.

**Phase 3: Software Engineering (Done)**
- [x] Write C++ firmware in Arduino IDE to read analog (MQ-135) and digital (DHT11) inputs.
- [x] Implement conditional logic to trigger specific LEDs based on defined threshold ranges.
- [x] Integrate buzzer activation tied to the Red LED (Danger) state.
