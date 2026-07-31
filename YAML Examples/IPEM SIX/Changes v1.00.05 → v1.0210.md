# IPEM SIX ESPHome Firmware

## Release Notes – v1.00.05 → v1.02.10 (July 31st 2026)

This development phase focused on transforming the firmware from a single-phase energy monitor into the foundation for a configurable **single-phase, split-phase and three-phase** power monitoring platform, while significantly improving diagnostics, commissioning and long-term monitoring.

----------

## v1.00.05 → v1.01.xx

### Firmware & Documentation

-   Improved firmware versioning.
-   Firmware version now matches release filename.
-   Expanded firmware metadata.
-   Improved diagnostics presentation.
-   General code clean-up and documentation improvements.

### Diagnostics

-   Added additional ESPHome diagnostic entities.
-   Improved configuration reporting.
-   Renamed diagnostic entities to clearly distinguish configuration values.
-   Added configuration entity category support.

### Voltage Monitoring

-   Introduced multiple line voltage architecture.
-   Added:
    -   Line Voltage L1
    -   Line Voltage L2
    -   Line Voltage L3
-   Prepared firmware for future split-phase and three-phase operation.

### Calibration

-   Expanded voltage calibration from

```
gain_voltage_baseline
```

to

```
gain_voltage_baseline1
gain_voltage_baseline2
gain_voltage_baseline3
```

allowing independent calibration for each voltage input.

### Board Configuration

Introduced configurable board parameters including:

-   Number of voltage inputs
-   Phase configuration
-   Future multi-phase support

----------

# Phase 2

## Multi-Phase Foundation

Introduced the framework required to support:

-   Single Phase
-   Split Phase
-   Three Phase

using

```
phases_inputs:
```

which becomes the master configuration controlling firmware behaviour.

----------

## Split Phase Mapping

Defined split-phase operation as:

```
L1
 ├─ CTA-1
 └─ CTB-1

L3
 ├─ CTA-3
 └─ CTB-3

CTA-2 / CTB-2
Not used
```

----------

## Three Phase Mapping

Prepared firmware for

```
L1 → CTA-1 / CTB-1
L2 → CTA-2 / CTB-2
L3 → CTA-3 / CTB-3
```

----------

# Voltage Diagnostics

Added new commissioning sensors.

### Line Voltages

-   Line Voltage L1
-   Line Voltage L2
-   Line Voltage L3

These allow each voltage input to be verified independently.

### Average Line Voltage

New calculated sensor providing the average of all active line voltages.

### Voltage Difference

New calculated sensor showing

```
Maximum Voltage - Minimum Voltage
```

allowing quick detection of voltage imbalance.

### Voltage Statistics

Added long-term statistics including

-   Minimum Line Voltage
-   Maximum Line Voltage

These retain the lowest and highest observed voltages until reset.

### Reset Voltage Statistics

New control button allowing voltage statistics to be cleared without rebooting the device.

----------

# LED Improvements

Improved WS2812 RGB status LED operation.

Added:

-   RGB power-up test
-   Single RGB colour cycle during boot
-   Automatic return to Green Heartbeat effect

This provides immediate visual confirmation of LED operation.

----------

# Diagnostics Improvements

Renamed several configuration entities to clearly distinguish configuration from measured values.

Examples include:

-   Config Banks
-   Config Current Inputs
-   Config Current Type
-   Config Phase Voltage

This makes the Diagnostics page easier to understand.

----------

# Configuration Improvements

Expanded board configuration ready for future firmware features.

Includes preparation for:

-   Voltage routing
-   Phase routing
-   Split-phase support
-   Three-phase support
-   Independent voltage calibration

----------

# Statistics Framework

Introduced the foundations for long-term commissioning statistics.

Voltage:

-   Minimum Line Voltage
-   Maximum Line Voltage
-   Average Line Voltage

Power framework prepared for:

-   Minimum CTA Power
-   Maximum CTA Power
-   Minimum CTB Power
-   Maximum CTB Power

----------

# Internal Improvements

-   Improved ESPHome entity naming.
-   Improved diagnostics organisation.
-   Reduced duplicated configuration.
-   Improved firmware structure for future expansion.
-   Prepared architecture for configurable CT-to-voltage mapping.
-   Improved maintainability of multi-phase logic.

----------

# Overall

The firmware has evolved from a **single-phase energy monitor** into a **configurable multi-phase monitoring platform**.

Major new capabilities include:

-   ✔ Independent voltage calibration
-   ✔ Multi-phase architecture
-   ✔ Enhanced diagnostics
-   ✔ Improved commissioning tools
-   ✔ Voltage statistics
-   ✔ RGB boot diagnostics
-   ✔ Foundation for split-phase and three-phase support
-   ✔ Framework for long-term power statistics

These releases establish the software architecture for the next development phase, which will implement full configurable CT-to-voltage mapping and complete multi-phase power calculation logic.