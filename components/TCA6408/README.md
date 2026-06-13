# TCA6408 ESPHome Component

Full-featured custom component for the **TCA6408** 8-bit I²C I/O Expander.

## Features
- 8 bidirectional GPIO pins
- Hardware polarity inversion (inputs)
- **Interrupt-driven** inputs (active-low)
- Polling fallback
- Cached GPIO expander (efficient)
- Works on ESP32 (incl. C5), ESP8266, etc.

## Installation

Copy the `tca6408` folder into your ESPHome project's `custom_components/` directory.

## Basic Configuration

```yaml
i2c:
  sda: GPIO4
  scl: GPIO5
  scan: true

custom_components:
  - source:
      type: local
      path: custom_components/tca6408

tca6408:
  - id: tca6408_hub
    address: 0x20                    # 0x20–0x27 depending on ADDR pins
    interrupt_pin: GPIO6             # Recommended for responsive inputs