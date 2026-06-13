#pragma once

#include "esphome/components/gpio_expander/cached_gpio.h"
#include "esphome/components/i2c/i2c.h"
#include "esphome/core/component.h"
#include "esphome/core/hal.h"

namespace esphome {
namespace tca6408 {

/**
 * TCA6408 8-bit I²C I/O Expander Component
 *
 * Features:
 * - 8 bidirectional GPIO pins (0-7)
 * - Hardware polarity inversion (for inputs)
 * - Interrupt support (active-low open-drain INT pin)
 * - Cached GPIO access for efficiency
 * - Works with ESP32 (including C5), ESP8266, etc.
 */
class TCA6408Component : public Component,
                         public i2c::I2CDevice,
                         public gpio_expander::CachedGpioExpander<uint8_t, 8> {
 public:
  void setup() override;
  void loop() override;
  void dump_config() override;
  float get_setup_priority() const override { return setup_priority::IO; }

  /** Set I²C address (default 0x20) */
  void set_address(uint8_t address) { this->address_ = address; }

  /** Set ESP GPIO connected to TCA6408 INT pin (recommended) */
  void set_interrupt_pin(InternalGPIOPin *pin) { this->interrupt_pin_ = pin; }

  /** Set hardware polarity inversion for a specific pin (used internally) */
  void set_polarity_inversion(uint8_t pin, bool inverted);

 protected:
  /** Interrupt Service Routine - lightweight, runs in ISR context */
  static void IRAM_ATTR gpio_intr(TCA6408Component *arg);

  // GPIO Expander overrides
  bool digital_read_hw(uint8_t pin) override;
  bool digital_read_cache(uint8_t pin) override;
  void digital_write_hw(uint8_t pin, bool value) override;
  void pin_mode(uint8_t pin, gpio::Flags flags) override;

  uint8_t mode_mask_{0xFF};      // 1 = input, 0 = output (Config Register 0x03)
  uint8_t output_mask_{0x00};    // Output Port Register 0x01
  uint8_t input_mask_{0x00};     // Input Port Register 0x00
  uint8_t polarity_mask_{0x00};  // Polarity Inversion Register 0x02 (1 = inverted)

  InternalGPIOPin *interrupt_pin_{nullptr};  // ESP pin connected to TCA6408 INT
  bool interrupt_triggered_{false};          // Flag set by ISR

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
