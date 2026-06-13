import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c
import esphome.pins as pins
from esphome.const import CONF_ID, CONF_ADDRESS, CONF_INTERRUPT_PIN

DEPENDENCIES = ["i2c"]

tca6408_ns = cg.esphome_ns.namespace("tca6408")
TCA6408Component = tca6408_ns.class_("TCA6408Component", cg.Component, i2c.I2CDevice)

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(TCA6408Component),
            cv.Optional(CONF_ADDRESS, default=0x20): cv.i2c_address,
            cv.Optional(CONF_INTERRUPT_PIN): pins.gpio_input_pin_schema,   # ← Fixed
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
    .extend(i2c.i2c_device_schema(0x20))
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

