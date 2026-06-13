import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c, gpio
from esphome.const import CONF_ID, CONF_ADDRESS, CONF_INTERRUPT_PIN
from esphome import pins

DEPENDENCIES = ["i2c"]

tca6408_ns = cg.esphome_ns.namespace("tca6408")

TCA6408Component = tca6408_ns.class_(
    "TCA6408Component", cg.Component, i2c.I2CDevice
)

TCA6408GPIOPin = tca6408_ns.class_("TCA6408GPIOPin", cg.GPIOPin)

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(TCA6408Component),
            cv.Optional(CONF_ADDRESS, default=0x20): cv.i2c_address,
            cv.Optional(CONF_INTERRUPT_PIN): gpio.gpio_input_pin_schema,
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
    .extend(i2c.i2c_device_schema(0x20))
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])

    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)

    cg.add(var.set_address(config[CONF_ADDRESS]))

    if CONF_INTERRUPT_PIN in config:
        pin = await gpio.register_gpio_pin(var, config[CONF_INTERRUPT_PIN])
        cg.add(var.set_interrupt_pin(pin))


# ===== PIN REGISTRATION =====

TCA6408_PIN_SCHEMA = gpio.gpio_base_schema(TCA6408GPIOPin).extend(
    {
        cv.Required("number"): cv.int_range(min=0, max=7),
    }
)

@pins.PIN_SCHEMA_REGISTRY.register("tca6408", TCA6408_PIN_SCHEMA)
async def tca6408_pin_to_code(config):
    var = cg.new_Pvariable(config["number"])
    yield var
