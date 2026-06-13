import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c, gpio
from esphome.const import CONF_ID, CONF_ADDRESS, CONF_INTERRUPT_PIN

DEPENDENCIES = ["i2c"]

tca6408_ns = cg.esphome_ns.namespace("tca6408")
TCA6408Component = tca6408_ns.class_("TCA6408Component", cg.Component, i2c.I2CDevice)

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(TCA6408Component),
            cv.Optional(CONF_ADDRESS, default=0x20): cv.i2c_address,
            cv.Optional(CONF_INTERRUPT_PIN): cv.validate_gpio_pin,
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
    .extend(i2c.i2c_device_schema(0x20))   # This is correct for new ESPHome
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)

    if CONF_ADDRESS in config:
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
