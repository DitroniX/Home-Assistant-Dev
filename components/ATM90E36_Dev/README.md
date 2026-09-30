# DitroniX ATM90E36 ESPHome component with I4 / Neutral support

# ATM90E36_Dev for IPEM S3-AI (September 2026 - Dave Williams - DitroniX Dev)

# This is a Development Component and so Work In Progress

Changes in this package:
- Correct ESPHome SPI transfer API using std::array.
- Adds phase_n / ATM90E36 I4 Neutral Current.
- Uses IGAINN 0x6D, IOFFSETN 0x6E and IRMSN 0xD8.
- Includes working phase_status and frequency_status text sensors.
- Does not require number components.

ESPHome YAML platform name:
  ATM90E36_Dev

Example:
  phase_n:
    current:
      name: "IPEM Neutral Current"
    gain_ct: 33500
    offset_current: 0

Text sensors:
  - platform: ATM90E36_Dev
    phase_status:
      name: "IPEM Phase Status"
    frequency_status:
      name: "IPEM Frequency Status"

This package is based on the current DitroniX ATM90E36 component structure. 

The repository already defines IGAINN, IOFFSETN and IRMSN; this modification exposes I4 through ESPHome YAML.
