import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c, gpio
from esphome.const import CONF_ID, CONF_ADDRESS, CONF_INTERRUPT_PIN

# This component depends on the I2C bus
DEPENDENCIES = ["i2c"]

# Namespace for the C++ component
tca6408_ns = cg.esphome_ns.namespace("tca6408")

# Reference to the main C++ class
TCA6408Component = tca6408_ns.class_("TCA6408Component", cg.Component, i2c.I2CDevice)

# Configuration schema for the component
CONFIG_SCHEMA = (
    cv.Schema(
        {
            # Unique ID for this component instance
            cv.GenerateID(): cv.declare_id(TCA6408Component),
            
            # I²C address of the TCA6408 (default 0x20 when ADDR pins are grounded)
            cv.Optional(CONF_ADDRESS, default=0x20): cv.i2c_address,
            
            # Optional ESP GPIO connected to the TCA6408 INT pin (recommended)
            # cv.Optional(CONF_INTERRUPT_PIN): gpio.validate_gpio_pin("internal"),
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
    .extend(i2c.i2c_device_schema())
)

async def to_code(config):
    """Generate C++ code from the YAML configuration."""
    
    var = cg.new_Pvariable(config[CONF_ID])
    
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)

    cg.add(var.set_address(config[CONF_ADDRESS]))

    if CONF_INTERRUPT_PIN in config:
        pin = await gpio.register_gpio_pin(var, config[CONF_INTERRUPT_PIN])
        cg.add(var.set_interrupt_pin(pin))


# ================================================
# YAML USAGE EXAMPLES
# ================================================

"""
# Example 1: Basic Outputs Only
tca6408:
  - id: tca6408_hub
    address: 0x20

switch:
  - platform: gpio
    name: "TCA6408 Output 0"
    pin:
      tca6408: tca6408_hub
      number: 0
      mode: OUTPUT


# Example 2: Full Configuration with Interrupt (Recommended)
i2c:
  sda: GPIO4
  scl: GPIO5
  scan: true

tca6408:
  - id: tca6408_hub
    address: 0x20
    interrupt_pin: GPIO6

# Outputs
switch:
  - platform: gpio
    name: "Relay (Active Low)"
    pin:
      tca6408: tca6408_hub
      number: 1
      mode: OUTPUT
      inverted: true

# Inputs
binary_sensor:
  - platform: gpio
    name: "Door Sensor"
    pin:
      tca6408: tca6408_hub
      number: 3
      mode: INPUT
      inverted: true
"""
