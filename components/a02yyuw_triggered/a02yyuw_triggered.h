#pragma once
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/output/binary_output.h"

namespace esphome {
namespace a02yyuw_triggered {

class A02YYUWTriggeredSensor : public PollingComponent, public sensor::Sensor {
 public:
  output::BinaryOutput *trigger_;
  uart::UARTComponent *uart_;

  A02YYUWTriggeredSensor(output::BinaryOutput *trigger, uart::UARTComponent *uart)
      : PollingComponent(500), trigger_(trigger), uart_(uart) {}

  void update() override;
};

}  // namespace a02yyuw_triggered
}  // namespace esphome
