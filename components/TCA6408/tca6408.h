#include "tca6408.h"
#include "esphome/core/log.h"

namespace esphome {
namespace tca6408 {

static const char *const TAG = "tca6408";

static const uint8_t TCA6408_INPUT_PORT    = 0x00;
static const uint8_t TCA6408_OUTPUT_PORT   = 0x01;
static const uint8_t TCA6408_POLARITY_PORT = 0x02;
static const uint8_t TCA6408_CONFIG_PORT   = 0x03;

void TCA6408Component::setup() {
  ESP_LOGCONFIG(TAG, "Setting up TCA6408...");

  // Initialize all registers
  if (this->write_register(TCA6408_POLARITY_PORT, 0x00) != i2c::ERROR_OK ||
      this->write_register(TCA6408_CONFIG_PORT, this->mode_mask_) != i2c::ERROR_OK ||
      !this->read_gpio_outputs_()) {
    this->mark_failed();
    return;
  }

  if (this->interrupt_pin_ != nullptr) {
    this->interrupt_pin_->setup();
    this->interrupt_pin_->pin_mode(gpio::FLAG_INPUT | gpio::FLAG_PULLUP);
    this->interrupt_pin_->attach_interrupt(&TCA6408Component::gpio_intr, this, gpio::INTERRUPT_FALLING_EDGE);
    this->set_invalidate_on_read_(false);
    ESP_LOGCONFIG(TAG, "  Interrupt mode enabled (active-low)");
  } else {
    this->enable_loop();
    ESP_LOGCONFIG(TAG, "  Polling mode enabled");
  }
}

// ... (gpio_intr, loop, dump_config stay the same)

bool TCA6408Component::read_gpio_outputs_() {
  if (this->is_failed()) return false;
  uint8_t data;
  if (this->read_register(TCA6408_OUTPUT_PORT, &data) != i2c::ERROR_OK) {
    this->status_set_warning();
    return false;
  }
  this->output_mask_ = data;
  this->status_clear_warning();
  return true;
}

// Rest of the file remains the same as you have it...
