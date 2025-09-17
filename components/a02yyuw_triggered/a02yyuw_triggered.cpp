#include "a02yyuw_triggered.h"
#include "esphome/core/log.h"

namespace esphome {
namespace a02yyuw_triggered {

static const char *const TAG = "a02yyuw";

void A02YYUWTriggeredSensor::update() {
  while (this->uart_->available()) {
    uint8_t dump;
    this->uart_->read_byte(&dump);
  }

  this->trigger_->turn_on();
  delay(30);
  this->trigger_->turn_off();
  delay(30);
  this->trigger_->turn_on();
  delay(60);

  uint8_t data[4] = {0};
  const uint32_t start = millis();
  int idx = 0;
  while (idx < 4 && (millis() - start) < 150) {
    uint8_t b;
    if (this->uart_->read_byte(&b)) {
      data[idx++] = b;
    } else {
      delay(1);
    }
  }

  if (idx < 4) {
    ESP_LOGW(TAG, "Timeout reading frame, got %d byte(s)", idx);
    return;
  }

  if (data[0] != 0xFF) {
    ESP_LOGW(TAG, "Bad header: %02X %02X %02X %02X", data[0], data[1], data[2], data[3]);
    return;
  }

  int distance_mm = (int)data[1] * 256 + data[2];
  uint8_t checksum_calc = (uint8_t)((data[0] + data[1] + data[2]) & 0xFF);
  if (checksum_calc != data[3]) {
    ESP_LOGW(TAG, "Checksum mismatch: calc=%02X recv=%02X", checksum_calc, data[3]);
    return;
  }

  this->publish_state(distance_mm);
}

}  // namespace a02yyuw_triggered
}  // namespace esphome

