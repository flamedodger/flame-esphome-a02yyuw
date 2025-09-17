import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, uart
from esphome.const import CONF_ID, UNIT_MILLIMETER, ICON_ARROW_EXPAND_VERTICAL, DEVICE_CLASS_DISTANCE, STATE_CLASS_MEASUREMENT

DEPENDENCIES = ["uart"]

a02yyuw_ns = cg.esphome_ns.namespace("a02yyuw_triggered")
A02YYUWSensor = a02yyuw_ns.class_("A02YYUWSensor", sensor.Sensor, cg.Component)

CONFIG_SCHEMA = sensor.sensor_schema(
    unit_of_measurement=UNIT_MILLIMETER,
    icon=ICON_ARROW_EXPAND_VERTICAL,
    accuracy_decimals=0,
    device_class=DEVICE_CLASS_DISTANCE,
    state_class=STATE_CLASS_MEASUREMENT,
).extend({
    cv.GenerateID(): cv.declare_id(A02YYUWSensor),
    cv.Required("uart_id"): cv.use_id(uart.UARTComponent),
})

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await sensor.register_sensor(var, config)
    uart_comp = await cg.get_variable(config["uart_id"])
    cg.add(var.set_uart(uart_comp))
