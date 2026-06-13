import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c
from esphome.const import CONF_ID, CONF_ADDRESS

DEPENDENCIES = ["i2c"]

tca6408_ns = cg.esphome_ns.namespace("tca6408")

TCA6408Component = tca6408_ns.class_(
    "TCA6408Component",
    cg.Component,
    i2c.I2CDevice
)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(TCA6408Component),
        cv.Optional(CONF_ADDRESS, default=0x20): cv.i2c_address,
    }
).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)
    cg.add(var.set_address(config[CONF_ADDRESS]))
