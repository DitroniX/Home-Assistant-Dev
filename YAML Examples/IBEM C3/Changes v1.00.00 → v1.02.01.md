# IBEM C3 Firmware Release Notes

## Version 1.02.01

**Release Date:** 01 August 2026

This release significantly improves configurability, diagnostics, usability, and persistence while simplifying the Home Assistant interface.

----------

# General

### Updated firmware

-   Firmware version updated to **v1.02.01**.
-   Include a Device name, such as Solar-Charger, or Battery 1, 2, 3 etc.
  
  ----------

# Configuration Improvements

## Current Threshold Configuration

Added configurable current thresholds for:

-   Current Low Threshold
-   Current Mid Threshold
-   Current High Threshold
-   Current Max Threshold

This for a next release for banding of currents.

Features include:

-   Home Assistant slider controls
-   Configuration entities
-   Threshold persistence across reboot
-   User configurable limits


## Restore Threshold Defaults

Added a configuration button to restore all thresholds to the firmware defaults.

This allows rapid recovery after experimentation or commissioning.


## Threshold Persistence

Threshold values are now retained after power loss and reboot.

This removes the need to reconfigure limits after restarting the device.



# Diagnostics

## Firmware Version

Firmware Version is now exposed as a Diagnostic entity.

Previously this was a configuration item.

This makes firmware identification much more intuitive.


## Board Target

Added:

```
Board Target
```

Diagnostic entity to clearly identify the compiled hardware target.

## PCB Temperature Status

Added a human readable PCB temperature status.

Instead of only displaying temperature, the firmware now reports states such as:

-   Cold
-   Cool
-   Normal
-   Warm
-   Hot
-   Very Hot

This greatly improves field diagnostics.

## LED Improvements

The manual RGB LED controls have been hidden.

These entities are now marked as internal because LED operation is now firmware controlled.

This prevents accidental user interference with heartbeat and alarm indication.

## Calibration

## Zero Store

Improved Zero Store calibration documentation.

Calibration now clearly states that current flow should be zero before calibration is performed.

You can click Zero Store, or Hold User Button to zero store.

## Boot Behaviour

Added an `on_boot` handler to restore operational settings during startup.

This ensures restored configuration values are immediately available after reboot.

## Home Assistant UI Improvements

The Configuration page is now significantly cleaner.

Configuration entities include:

-   Current Low Threshold
-   Current Mid Threshold
-   Current High Threshold
-   Current Max Threshold
-   Restore Threshold Defaults

Diagnostic entities include:

-   Firmware Version
-   Board Target
-   PCB Temperature Status

## Internal Improvements

-   Added configuration persistence.
-   Added additional diagnostic reporting.
-   Improved firmware metadata.
-   Simplified user interface.
-   Reduced manual controls.
-   Better separation of Configuration and Diagnostic entities.

# Summary

### New Features

-   ✅ Current Low Threshold
-   ✅ Current Mid Threshold
-   ✅ Current High Threshold
-   ✅ Current Max Threshold
-   ✅ Threshold persistence
-   ✅ Restore Threshold Defaults button
-   ✅ Firmware Version diagnostic
-   ✅ Board Target diagnostic
-   ✅ PCB Temperature Status
-   ✅ Improved boot restoration
-   ✅ Cleaner Home Assistant interface
-   ✅ Hidden manual RGB LED controls

### Overall

Version **1.02.01** represents a substantial usability improvement over **v1.01.00**, with a stronger focus on configuration persistence, diagnostics, and a simplified Home Assistant experience. 