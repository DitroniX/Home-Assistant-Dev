#pragma once

#include "esphome/components/gpio_expander/cached_gpio.h"
#include "esphome/components/i2c/i2c.h"
#include "esphome/core/component.h"
#include "esphome/core/hal.h"

namespace esphome {
namespace tca6408 {

class TCA6408Component : public Component,
                         public i2c::I2CDevice,
                         public gpio_expander::CachedGpioExpander<uint8_t, 8> {
 public:
  void setup() override;
  void loop() override;
  void dump_config() override;
  float get_setup_priority() const override { return setup_priority::IO; }

  void set_address(uint8_t address) { this->address_ = address; }
  void set_interrupt_pin(InternalGPIOPin *pin) { this->interrupt_pin_ = pin; }

  void set_polarity_inversion(uint8_t pin, bool inverted);

 protected:
  static void IRAM_ATTR gpio_intr(TCA6408Component *arg);

  bool digital_read_hw(uint8_t pin) override;
  bool digital_read_cache(uint8_t pin) override;
  void digital_write_hw(uint8_t pin, bool value) override;
  void pin_mode(uint8_t pin, gpio::Flags flags) override;

  uint8_t mode_mask_{0xFF};      // 1 = input, 0 = output
  uint8_t output_mask_{0x00};
  uint8_t input_mask_{0x00};
  uint8_t polarity_mask_{0x00};  // 1 = inverted (hardware polarity for inputs)

  InternalGPIOPin *interrupt_pin_{nullptr};
  bool interrupt_triggered_{false};

 private:
  bool read_gpio_outputs_();
};

class TCA6408GPIOPin : public gpio::GPIOPin, public Parented<TCA6408Component> {
 public:
  void setup() override;
  void pin_mode(gpio::Flags flags) override;
  bool digital_read() override;
  void digital_write(bool value) override;
  size_t dump_summary(char *buffer, size_t len) const override;

  void set_pin(uint8_t pin) { pin_ = pin; }
  void set_inverted(bool inverted);
  void set_flags(gpio::Flags flags) { flags_ = flags; }
  gpio::Flags get_flags() const override { return flags_; }

 protected:
  uint8_t pin_{0};
  bool inverted_{false};
  gpio::Flags flags_{0};
};

}  // namespace tca6408
}  // namespace esphome
