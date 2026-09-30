#pragma once
#include <cinttypes>
#include <string>
#include "atm90e36_reg.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/spi/spi.h"
#include "esphome/core/component.h"

namespace esphome {
namespace atm90e36 {

class ATM90E36Component : public PollingComponent,
    public spi::SPIDevice<spi::BIT_ORDER_MSB_FIRST, spi::CLOCK_POLARITY_HIGH,
                          spi::CLOCK_PHASE_TRAILING, spi::DATA_RATE_2MHZ> {
 public:
  static const uint8_t PHASEA = 0;
  static const uint8_t PHASEB = 1;
  static const uint8_t PHASEC = 2;

  void loop() override;
  void setup() override;
  void dump_config() override;
  void update() override;

  void set_voltage_sensor(int p, sensor::Sensor *s) { phase_[p].voltage_sensor_ = s; }
  void set_current_sensor(int p, sensor::Sensor *s) { phase_[p].current_sensor_ = s; }
  void set_power_sensor(int p, sensor::Sensor *s) { phase_[p].power_sensor_ = s; }
  void set_reactive_power_sensor(int p, sensor::Sensor *s) { phase_[p].reactive_power_sensor_ = s; }
  void set_apparent_power_sensor(int p, sensor::Sensor *s) { phase_[p].apparent_power_sensor_ = s; }
  void set_power_factor_sensor(int p, sensor::Sensor *s) { phase_[p].power_factor_sensor_ = s; }
  void set_forward_active_energy_sensor(int p, sensor::Sensor *s) { phase_[p].forward_active_energy_sensor_ = s; }
  void set_reverse_active_energy_sensor(int p, sensor::Sensor *s) { phase_[p].reverse_active_energy_sensor_ = s; }
  void set_phase_angle_sensor(int p, sensor::Sensor *s) { phase_[p].phase_angle_sensor_ = s; }
  void set_harmonic_active_power_sensor(int p, sensor::Sensor *s) { phase_[p].harmonic_active_power_sensor_ = s; }
  void set_peak_current_sensor(int p, sensor::Sensor *s) { phase_[p].peak_current_sensor_ = s; }
  void set_volt_gain(int p, uint16_t g) { phase_[p].voltage_gain_ = g; }
  void set_ct_gain(int p, uint16_t g) { phase_[p].ct_gain_ = g; }

  void set_neutral_current_sensor(sensor::Sensor *s) { neutral_current_sensor_ = s; }
  void set_neutral_ct_gain(uint16_t g) { neutral_ct_gain_ = g; }
  void set_neutral_current_offset(int offset) { neutral_current_offset_ = offset; }

  void set_freq_sensor(sensor::Sensor *s) { freq_sensor_ = s; }
  void set_chip_temperature_sensor(sensor::Sensor *s) { chip_temperature_sensor_ = s; }
  void set_line_freq(int f) { line_freq_ = f; }
  void set_current_phases(int p) { current_phases_ = p; }
  void set_pga_current(uint16_t g) { pga_current_ = g; }
  void set_pga_voltage(uint16_t g) { pga_voltage_ = g; }
  void set_dpga_gain(uint16_t g) { dpga_gain_ = g; }
  void set_peak_current_signed(bool v) { peak_current_signed_ = v; }

 protected:
  struct Phase {
    uint16_t voltage_gain_{0};
    uint16_t ct_gain_{0};
    float voltage_{0};
    float current_{0};
    float active_power_{0};
    float reactive_power_{0};
    float apparent_power_{0};
    float power_factor_{0};
    float forward_active_energy_{0};
    float reverse_active_energy_{0};
    float phase_angle_{0};
    float harmonic_active_power_{0};
    float peak_current_{0};
    sensor::Sensor *voltage_sensor_{nullptr};
    sensor::Sensor *current_sensor_{nullptr};
    sensor::Sensor *power_sensor_{nullptr};
    sensor::Sensor *reactive_power_sensor_{nullptr};
    sensor::Sensor *apparent_power_sensor_{nullptr};
    sensor::Sensor *power_factor_sensor_{nullptr};
    sensor::Sensor *forward_active_energy_sensor_{nullptr};
    sensor::Sensor *reverse_active_energy_sensor_{nullptr};
    sensor::Sensor *phase_angle_sensor_{nullptr};
    sensor::Sensor *harmonic_active_power_sensor_{nullptr};
    sensor::Sensor *peak_current_sensor_{nullptr};
    uint32_t cumulative_forward_active_energy_{0};
    uint32_t cumulative_reverse_active_energy_{0};
  } phase_[3];

  uint16_t read16_(uint16_t reg);
  void write16_(uint16_t reg, uint16_t val, bool validate = true);
  float get_phase_voltage_(uint8_t p);
  float get_phase_current_(uint8_t p);
  float get_phase_active_power_(uint8_t p);
  float get_phase_reactive_power_(uint8_t p);
  float get_phase_apparent_power_(uint8_t p);
  float get_phase_power_factor_(uint8_t p);
  float get_phase_forward_active_energy_(uint8_t p);
  float get_phase_reverse_active_energy_(uint8_t p);
  float get_phase_angle_(uint8_t p);
  float get_phase_harmonic_active_power_(uint8_t p);
  float get_phase_peak_current_(uint8_t p);
  float get_neutral_current_();
  float get_frequency_();
  float get_chip_temperature_();
  bool validate_spi_read_(uint16_t expected, const char *context = nullptr);

  sensor::Sensor *neutral_current_sensor_{nullptr};
  uint16_t neutral_ct_gain_{27961};
  int16_t neutral_current_offset_{0};
  sensor::Sensor *freq_sensor_{nullptr};
  sensor::Sensor *chip_temperature_sensor_{nullptr};

  uint16_t pga_current_{0x15};
  uint16_t pga_voltage_{0x15};
  uint16_t dpga_gain_{0x2};
  int line_freq_{50};
  int current_phases_{3};
  bool publish_interval_flag_{false};
  bool peak_current_signed_{false};
  uint16_t pga_cal_{0};
};

}  // namespace atm90e36
}  // namespace esphome
