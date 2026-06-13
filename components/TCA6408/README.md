# TCA6408 ESPHome Component

Full-featured custom component for the **TCA6408** 8-bit I²C I/O Expander.

## Features

- 8 bidirectional GPIO pins
- Hardware polarity inversion support (inputs)
- Interrupt-driven inputs (active-low INT pin)
- Efficient cached GPIO expander
- Polling fallback mode
- Compatible with ESP32 (including C3/C5/C6), ESP8266, etc.

## Installation

1. Download or clone this component into your ESPHome project:
   ```bash
   mkdir -p custom_components
   cp -r TCA6408/custom_components/tca6408 custom_components/