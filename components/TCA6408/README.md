# TCA6408 ESPHome Component

Full-featured custom component for the **TCA6408** 8-bit I²C I/O Expander.

## Features

- 8 bidirectional GPIO pins
- Hardware polarity inversion support (inputs)
- Interrupt-driven inputs (active-low INT pin)
- Efficient cached GPIO expander
- Polling fallback mode
- Compatible with ESP32 (including C3/C5/C6), ESP8266, etc.

The INT pin on TCA6408 is open-drain active-low — connect a pull-up resistor (or use internal pull-up on ESP).

## Installation

1. Download or clone this component into your ESPHome project:
   ```bash
   mkdir -p custom_components
   cp -r TCA6408/custom_components/tca6408 custom_components/
## Basic Configuration

	i2c:
	  sda: GPIO4
	  scl: GPIO5
	  scan: true
	  frequency: 400kHz

	custom_components:
	  - source:
	      type: local
	      path: custom_components/tca6408

	tca6408:
	  - id: tca6408_hub
	    address: 0x20                    # Default: 0x20 (0x20–0x27 depending on ADDR pins)
	    interrupt_pin: GPIO6             # Recommended for fast input response

## Example: Outputs (Switches)

	switch:
	  - platform: gpio
	    name: "TCA6408 Output 0"
	    pin:
	      tca6408: tca6408_hub
	      number: 0
	      mode: OUTPUT

	  - platform: gpio
	    name: "TCA6408 Relay (Active Low)"
	    pin:
	      tca6408: tca6408_hub
	      number: 1
	      mode: OUTPUT
	      inverted: true

## Example: Inputs (Binary Sensors) with Interrupt

	binary_sensor:
	  - platform: gpio
	    name: "Door Sensor"
	    pin:
	      tca6408: tca6408_hub
	      number: 3
	      mode: INPUT
	      inverted: true           # Uses hardware polarity inversion

	  - platform: gpio
	    name: "Push Button"
	    pin:
	      tca6408: tca6408_hub
	      number: 4
	      mode: INPUT

