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
  ESP_LOGCONFIG(TAG, "Setting up TCA6408 at address 0x%02X...", this->address_);

  // Initialize registers to known state
  if (this->write_register(TCA6408_POLARITY_PORT, 0x00) != i2c::ERROR_OK) {
    ESP_LOGE(TAG, "Failed to write polarity register");
    this->mark_failed();
    return;
  }

  if (this->write_register(TCA6408_CONFIG_PORT, this->mode_mask_) != i2c::ERROR_OK) {
    ESP_LOGE(TAG, "Failed to write config register");
    this->mark_failed();
    return;
  }

  if (!this->read_gpio_outputs_()) {
    ESP_LOGE(TAG, "Failed to read output register");
    this->mark_failed();
    return;
  }

  if (this->interrupt_pin_ != nullptr) {
    this->interrupt_pin_->setup();
    this->interrupt_pin_->pin_mode(gpio::FLAG_INPUT | gpio::FLAG_PULLUP);
    this->interrupt_pin_->attach_interrupt(&TCA6408Component::gpio_intr, this,
                                           gpio::INTERRUPT_FALLING_EDGE);
    this->set_invalidate_on_read_(false);
    ESP_LOGCONFIG(TAG, "  Interrupt mode enabled (active-low INT)");
  } else {
    this->enable_loop();
    ESP_LOGCONFIG(TAG, "  Polling mode enabled");
  }

  ESP_LOGCONFIG(TAG, "  Setup complete");
}

void IRAM_ATTR TCA6408Component::gpio_intr(TCA6408Component *arg) {
  arg->interrupt_triggered_ = true;
  arg->enable_loop_soon_any_context();
}

void TCA6408Component::loop() {
  if (this->interrupt_triggered_) {
    this->interrupt_triggered_ = false;

    // Reading input port clears the interrupt on TCA6408
    this->digital_read_hw(0);  // pin number is ignored, reads all 8 bits
    this->reset_pin_cache_();

    // If INT line is high again, disable loop until next interrupt
    if (this->interrupt_pin_ && this->interrupt_pin_->digital_read()) {
      this->disable_loop();
    }
  }
}

void TCA6408Component::dump_config() {
  ESP_LOGCONFIG(TAG, "TCA6408:");
  LOG_I2C_DEVICE(this);
  ESP_LOGCONFIG(TAG, "  Address: 0x%02X", this->address_);
  LOG_PIN("  Interrupt Pin: ", this->interrupt_pin_);
  ESP_LOGCONFIG(TAG, "  Mode Mask: 0x%02X (1=input)", this->mode_mask_);
  ESP_LOGCONFIG(TAG, "  Polarity Mask: 0x%02X", this->polarity_mask_);
}

bool TCA6408Component::read_gpio_outputs_() {
  if (this->is_failed()) return false;
  uint8_t data = 0;
  if (this->read_register(TCA6408_OUTPUT_PORT, &data) != i2c::ERROR_OK) {
    this->status_set_warning();
    return false;
  }
  this->output_mask_ = data;
  this->status_clear_warning();
  return true;
}

bool TCA6408Component::digital_read_hw(uint8_t pin) {
  if (this->is_failed()) return false;

  uint8_t data = 0;
  if (this->read_register(TCA6408_INPUT_PORT, &data) != i2c::ERROR_OK) {
    this->status_set_warning();
    return false;
  }
  this->input_mask_ = data;
  this->status_clear_warning();
  return true;
}

void TCA6408Component::digital_write_hw(uint8_t pin, bool value) {
  if (this->is_failed()) return;

  if (value) {
    this->output_mask_ |= (1U << pin);
  } else {
    this->output_mask_ &= ~(1U << pin);
  }

  if (this->write_register(TCA6408_OUTPUT_PORT, this->output_mask_) != i2c::ERROR_OK) {
    this->status_set_warning();
  } else {
    this->status_clear_warning();
  }
}

void TCA6408Component::pin_mode(uint8_t pin, gpio::Flags flags) {
  if (flags & gpio::FLAG_OUTPUT) {
    this->mode_mask_ &= ~(1U << pin);  // 0 = output
  } else {
    this->mode_mask_ |= (1U << pin);   // 1 = input
    if (this->interrupt_pin_ == nullptr) {
      this->enable_loop();
    }
  }
  this->write_register(TCA6408_CONFIG_PORT, this->mode_mask_);
}

void TCA6408Component::set_polarity_inversion(uint8_t pin, bool inverted) {
  if (inverted) {
    this->polarity_mask_ |= (1U << pin);
  } else {
    this->polarity_mask_ &= ~(1U << pin);
  }
  this->write_register(TCA6408_POLARITY_PORT, this->polarity_mask_);
}

bool TCA6408Component::digital_read_cache(uint8_t pin) {
  bool value = (this->input_mask_ & (1U << pin)) != 0;
  // Apply hardware polarity inversion if set
  if (this->polarity_mask_ & (1U << pin)) {
    value = !value;
  }
  return value;
}

// ====================== TCA6408GPIOPin ======================

void TCA6408GPIOPin::setup() {
  this->pin_mode(this->flags_);
  if (this->inverted_) {
    this->parent_->set_polarity_inversion(this->pin_, true);
  }
}

void TCA6408GPIOPin::set_inverted(bool inverted) {
  this->inverted_ = inverted;
  if (this->parent_ != nullptr) {
    this->parent_->set_polarity_inversion(this->pin_, inverted);
  }
}

void TCA6408GPIOPin::pin_mode(gpio::Flags flags) {
  this->flags_ = flags;
  this->parent_->pin_mode(this->pin_, flags);
}

bool TCA6408GPIOPin::digital_read() {
  return this->parent_->digital_read(this->pin_) != this->inverted_;
}

void TCA6408GPIOPin::digital_write(bool value) {
  this->parent_->digital_write(this->pin_, value != this->inverted_);
}

size_t TCA6408GPIOPin::dump_summary(char *buffer, size_t len) const {
  return snprintf(buffer, len, "%u via TCA6408@0x%02X", this->pin_, this->parent_->address_);
}

}  // namespace tca6408
}  // namespace esphome
