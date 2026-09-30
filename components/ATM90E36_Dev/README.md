# DitroniX ATM90E36 ESPHome component with I4 / Neutral support

Modified for IPEM S3-AI 3P4W operation.

## Added

- `phase_n:` YAML section
- Neutral current sensor
- I4 RMS current read from `IRMSN` register `0xD8`
- Configurable I4 CT gain using `IGAINN` register `0x6D`
- Configurable I4 current offset using `IOFFSETN` register `0x6E`

## Example

```yaml
- platform: ATM90E36
  id: ipem_atm90e36
  cs_pin: GPIO4

  phase_n:
    current:
      name: "IPEM Neutral Current"
      id: NEUTRALCURRENT
    gain_ct: 33500
    offset_current: 0
```

This package is based on the current DitroniX ATM90E36 component structure. The repository already defines IGAINN, IOFFSETN and IRMSN; this modification exposes I4 through ESPHome YAML.
