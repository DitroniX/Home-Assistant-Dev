import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import text_sensor

from . import ATM90E36Component

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.use_id(ATM90E36Component),
    cv.Optional("phase_status"): text_sensor.text_sensor_schema(),
    cv.Optional("frequency_status"): text_sensor.text_sensor_schema(),
})

async def to_code(config):
    var = await cg.get_variable(config["id"])

    if item := config.get("phase_status"):
        sens = await text_sensor.new_text_sensor(item)
        cg.add(var.set_phase_status_text_sensor(sens))

    if item := config.get("frequency_status"):
        sens = await text_sensor.new_text_sensor(item)
        cg.add(var.set_freq_status_text_sensor(sens))
