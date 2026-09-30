#include "atm90e36.h"
#include <cmath>
#include "esphome/core/log.h"

namespace esphome {
namespace atm90e36 {

static const char *const TAG = "atm90e36";

void ATM90E36Component::loop() {
  if (!publish_interval_flag_) return;
  publish_interval_flag_ = false;

  for (uint8_t p = 0; p < 3; p++) {
    if (phase_[p].voltage_sensor_) phase_[p].voltage_sensor_->publish_state(get_phase_voltage_(p));
    if (phase_[p].current_sensor_) phase_[p].current_sensor_->publish_state(get_phase_current_(p));
    if (phase_[p].power_sensor_) phase_[p].power_sensor_->publish_state(get_phase_active_power_(p));
    if (phase_[p].reactive_power_sensor_) phase_[p].reactive_power_sensor_->publish_state(get_phase_reactive_power_(p));
    if (phase_[p].apparent_power_sensor_) phase_[p].apparent_power_sensor_->publish_state(get_phase_apparent_power_(p));
    if (phase_[p].power_factor_sensor_) phase_[p].power_factor_sensor_->publish_state(get_phase_power_factor_(p));
    if (phase_[p].forward_active_energy_sensor_) phase_[p].forward_active_energy_sensor_->publish_state(get_phase_forward_active_energy_(p));
    if (phase_[p].reverse_active_energy_sensor_) phase_[p].reverse_active_energy_sensor_->publish_state(get_phase_reverse_active_energy_(p));
    if (phase_[p].phase_angle_sensor_) phase_[p].phase_angle_sensor_->publish_state(get_phase_angle_(p));
    if (phase_[p].harmonic_active_power_sensor_) phase_[p].harmonic_active_power_sensor_->publish_state(get_phase_harmonic_active_power_(p));
    if (phase_[p].peak_current_sensor_) phase_[p].peak_current_sensor_->publish_state(get_phase_peak_current_(p));
  }

  if (neutral_current_sensor_)
    neutral_current_sensor_->publish_state(get_neutral_current_());
  if (freq_sensor_)
    freq_sensor_->publish_state(get_frequency_());
  if (chip_temperature_sensor_)
    chip_temperature_sensor_->publish_state(get_chip_temperature_());

  update_status_text_();
}

void ATM90E36Component::update() {
  publish_interval_flag_ = true;
}

void ATM90E36Component::setup() {
  spi_setup();

  uint16_t mmode0 = 0x87;  // 3P4W, 50 Hz
  if (line_freq_ == 60) mmode0 |= 1 << 12;
  if (current_phases_ == 2) mmode0 |= 1 << 8;

  pga_cal_ = pga_current_;
  pga_cal_ |= pga_voltage_ << 8;
  pga_cal_ |= dpga_gain_ << 14;

  write16_(ATM90E36_REGISTER_SOFTRESET, 0x789A, false);
  delay(6);

  write16_(ATM90E36_REGISTER_CONFIGSTART, 0x5678);
  write16_(ATM90E36_REGISTER_PLCONSTH, 0x0861);
  write16_(ATM90E36_REGISTER_PLCONSTL, 0xC468);
  write16_(ATM90E36_REGISTER_MMODE0, mmode0);
  write16_(ATM90E36_REGISTER_MMODE1, pga_cal_);

  write16_(ATM90E36_REGISTER_CALSTART, 0x5678);
  write16_(ATM90E36_REGISTER_PQGAINA, 0);
  write16_(ATM90E36_REGISTER_PHIA, 0);
  write16_(ATM90E36_REGISTER_PQGAINB, 0);
  write16_(ATM90E36_REGISTER_PHIB, 0);
  write16_(ATM90E36_REGISTER_PQGAINC, 0);
  write16_(ATM90E36_REGISTER_PHIC, 0);

  write16_(ATM90E36_REGISTER_ADJSTART, 0x5678);

  write16_(ATM90E36_REGISTER_UGAINA, phase_[0].voltage_gain_);
  write16_(ATM90E36_REGISTER_IGAINA, phase_[0].ct_gain_);
  write16_(ATM90E36_REGISTER_UOFFSETA, 0);
  write16_(ATM90E36_REGISTER_IOFFSETA, 0);

  write16_(ATM90E36_REGISTER_UGAINB, phase_[1].voltage_gain_);
  write16_(ATM90E36_REGISTER_IGAINB, phase_[1].ct_gain_);
  write16_(ATM90E36_REGISTER_UOFFSETB, 0);
  write16_(ATM90E36_REGISTER_IOFFSETB, 0);

  write16_(ATM90E36_REGISTER_UGAINC, phase_[2].voltage_gain_);
  write16_(ATM90E36_REGISTER_IGAINC, phase_[2].ct_gain_);
  write16_(ATM90E36_REGISTER_UOFFSETC, 0);
  write16_(ATM90E36_REGISTER_IOFFSETC, 0);

  // I4 / Neutral
  write16_(ATM90E36_REGISTER_IGAINN, neutral_ct_gain_);
  write16_(ATM90E36_REGISTER_IOFFSETN, static_cast<uint16_t>(neutral_current_offset_));

  write16_(ATM90E36_REGISTER_CS3, 0x02F6);
}

void ATM90E36Component::dump_config() {
  ESP_LOGCONFIG(TAG, "ATM90E36:");
  LOG_PIN("  CS Pin: ", cs_);
  LOG_UPDATE_INTERVAL(this);
  LOG_SENSOR("  ", "Neutral Current", neutral_current_sensor_);
  LOG_SENSOR("  ", "Frequency", freq_sensor_);
  LOG_SENSOR("  ", "Chip Temperature", chip_temperature_sensor_);
  LOG_TEXT_SENSOR("  ", "Phase Status", phase_status_sensor_);
  LOG_TEXT_SENSOR("  ", "Frequency Status", frequency_status_sensor_);
}

uint16_t ATM90E36Component::read16_(uint16_t reg) {
  std::array<uint8_t, 3> data = {
      static_cast<uint8_t>(reg & 0x7F),
      0x00,
      0x00
  };

  enable();
  transfer_array(data);
  disable();

  return (static_cast<uint16_t>(data[1]) << 8) | data[2];
}

void ATM90E36Component::write16_(uint16_t reg, uint16_t val, bool validate) {
  std::array<uint8_t, 3> data = {
      static_cast<uint8_t>(reg | 0x80),
      static_cast<uint8_t>(val >> 8),
      static_cast<uint8_t>(val & 0xFF)
  };

  enable();
  transfer_array(data);
  disable();

  if (validate)
    validate_spi_read_(val, "write16_");
}

float ATM90E36Component::get_phase_voltage_(uint8_t p) {
  uint16_t v = read16_(ATM90E36_REGISTER_URMS + p);
  if (v < 50) v = 0;
  return v / 100.0f;
}

float ATM90E36Component::get_phase_current_(uint8_t p) {
  return read16_(ATM90E36_REGISTER_IRMS + p) / 1000.0f;
}

float ATM90E36Component::get_phase_active_power_(uint8_t p) {
  uint16_t v = read16_(ATM90E36_REGISTER_PMEAN + p);
  return v == 0xFFFF ? 0.0f : static_cast<float>(v);
}

float ATM90E36Component::get_phase_reactive_power_(uint8_t p) {
  return static_cast<int16_t>(read16_(ATM90E36_REGISTER_QMEAN + p)) / 1000.0f;
}

float ATM90E36Component::get_phase_apparent_power_(uint8_t p) {
  return read16_(ATM90E36_REGISTER_SMEANA + p);
}

float ATM90E36Component::get_phase_power_factor_(uint8_t p) {
  return static_cast<int16_t>(read16_(ATM90E36_REGISTER_PFMEAN + p)) / 1000.0f;
}

float ATM90E36Component::get_phase_forward_active_energy_(uint8_t p) {
  uint16_t v = read16_(ATM90E36_REGISTER_APENERGY + p);
  phase_[p].cumulative_forward_active_energy_ += v;
  return phase_[p].cumulative_forward_active_energy_ * (10.0f / 3200.0f);
}

float ATM90E36Component::get_phase_reverse_active_energy_(uint8_t p) {
  uint16_t v = read16_(ATM90E36_REGISTER_ANENERGY + p);
  phase_[p].cumulative_reverse_active_energy_ += v;
  return phase_[p].cumulative_reverse_active_energy_ * (10.0f / 3200.0f);
}

float ATM90E36Component::get_phase_angle_(uint8_t p) {
  float v = static_cast<int16_t>(read16_(ATM90E36_REGISTER_PANGLE + p)) / 10.0f;
  return v > 180.0f ? v - 360.0f : v;
}

float ATM90E36Component::get_phase_harmonic_active_power_(uint8_t p) {
  return static_cast<int16_t>(read16_(ATM90E36_REGISTER_PMEANH + p));
}

float ATM90E36Component::get_phase_peak_current_(uint8_t p) {
  int16_t v = static_cast<int16_t>(read16_(ATM90E36_REGISTER_IPEAK + p));
  if (!peak_current_signed_) v = std::abs(v);
  return v * phase_[p].ct_gain_ / 8192000.0f;
}

float ATM90E36Component::get_neutral_current_() {
  return read16_(ATM90E36_REGISTER_IRMSN) / 1000.0f;
}

float ATM90E36Component::get_frequency_() {
  return read16_(ATM90E36_REGISTER_FREQ) / 100.0f;
}

float ATM90E36Component::get_chip_temperature_() {
  return static_cast<int16_t>(read16_(ATM90E36_REGISTER_TEMP));
}

void ATM90E36Component::update_status_text_() {
  if (phase_status_sensor_) {
    float a = get_phase_voltage_(0);
    float b = get_phase_voltage_(1);
    float c = get_phase_voltage_(2);

    if (a < 100.0f && b < 100.0f && c < 100.0f)
      phase_status_sensor_->publish_state("Voltage Fault");
    else if (a < 200.0f || b < 200.0f || c < 200.0f)
      phase_status_sensor_->publish_state("Voltage Warning");
    else
      phase_status_sensor_->publish_state("Healthy");
  }

  if (frequency_status_sensor_) {
    float f = get_frequency_();

    if (f < 45.0f || f > 55.0f)
      frequency_status_sensor_->publish_state("Frequency Fault");
    else if (f < 49.0f || f > 51.0f)
      frequency_status_sensor_->publish_state("Frequency Warning");
    else
      frequency_status_sensor_->publish_state("Healthy");
  }
}

bool ATM90E36Component::validate_spi_read_(uint16_t expected, const char *context) {
  uint16_t last = read16_(ATM90E36_REGISTER_LASTSPIDATA);

  if (last != expected) {
    ESP_LOGW(TAG, "[%s] SPI read mismatch: expected 0x%04X, got 0x%04X",
             context ? context : "SPI", expected, last);
    return false;
  }

  return true;
}

}  // namespace atm90e36
}  // namespace esphome
