#pragma once
#include <cinttypes>

namespace esphome {
namespace atm90e36 {

static const uint16_t ATM90E36_REGISTER_SOFTRESET = 0x00;
static const uint16_t ATM90E36_REGISTER_SYSSTATUS0 = 0x01;
static const uint16_t ATM90E36_REGISTER_SYSSTATUS1 = 0x02;
static const uint16_t ATM90E36_REGISTER_FUNCEN0 = 0x03;
static const uint16_t ATM90E36_REGISTER_FUNCEN1 = 0x04;
static const uint16_t ATM90E36_REGISTER_SAGTH = 0x08;
static const uint16_t ATM90E36_REGISTER_LASTSPIDATA = 0x0F;
static const uint16_t ATM90E36_REGISTER_CONFIGSTART = 0x30;
static const uint16_t ATM90E36_REGISTER_PLCONSTH = 0x31;
static const uint16_t ATM90E36_REGISTER_PLCONSTL = 0x32;
static const uint16_t ATM90E36_REGISTER_MMODE0 = 0x33;
static const uint16_t ATM90E36_REGISTER_MMODE1 = 0x34;
static const uint16_t ATM90E36_REGISTER_CALSTART = 0x40;
static const uint16_t ATM90E36_REGISTER_POFFSETA = 0x41;
static const uint16_t ATM90E36_REGISTER_QOFFSETA = 0x42;
static const uint16_t ATM90E36_REGISTER_POFFSETB = 0x43;
static const uint16_t ATM90E36_REGISTER_QOFFSETB = 0x44;
static const uint16_t ATM90E36_REGISTER_POFFSETC = 0x45;
static const uint16_t ATM90E36_REGISTER_QOFFSETC = 0x46;
static const uint16_t ATM90E36_REGISTER_PQGAINA = 0x47;
static const uint16_t ATM90E36_REGISTER_PHIA = 0x48;
static const uint16_t ATM90E36_REGISTER_PQGAINB = 0x49;
static const uint16_t ATM90E36_REGISTER_PHIB = 0x4A;
static const uint16_t ATM90E36_REGISTER_PQGAINC = 0x4B;
static const uint16_t ATM90E36_REGISTER_PHIC = 0x4C;
static const uint16_t ATM90E36_REGISTER_CS1 = 0x4D;
static const uint16_t ATM90E36_REGISTER_HARMSTART = 0x50;
static const uint16_t ATM90E36_REGISTER_POFFSETAF = 0x51;
static const uint16_t ATM90E36_REGISTER_POFFSETBF = 0x52;
static const uint16_t ATM90E36_REGISTER_POFFSETCF = 0x53;
static const uint16_t ATM90E36_REGISTER_PGAINAF = 0x54;
static const uint16_t ATM90E36_REGISTER_PGAINBF = 0x55;
static const uint16_t ATM90E36_REGISTER_PGAINCF = 0x56;
static const uint16_t ATM90E36_REGISTER_CS2 = 0x57;
static const uint16_t ATM90E36_REGISTER_ADJSTART = 0x60;
static const uint16_t ATM90E36_REGISTER_UGAINA = 0x61;
static const uint16_t ATM90E36_REGISTER_IGAINA = 0x62;
static const uint16_t ATM90E36_REGISTER_UOFFSETA = 0x63;
static const uint16_t ATM90E36_REGISTER_IOFFSETA = 0x64;
static const uint16_t ATM90E36_REGISTER_UGAINB = 0x65;
static const uint16_t ATM90E36_REGISTER_IGAINB = 0x66;
static const uint16_t ATM90E36_REGISTER_UOFFSETB = 0x67;
static const uint16_t ATM90E36_REGISTER_IOFFSETB = 0x68;
static const uint16_t ATM90E36_REGISTER_UGAINC = 0x69;
static const uint16_t ATM90E36_REGISTER_IGAINC = 0x6A;
static const uint16_t ATM90E36_REGISTER_UOFFSETC = 0x6B;
static const uint16_t ATM90E36_REGISTER_IOFFSETC = 0x6C;
static const uint16_t ATM90E36_REGISTER_IGAINN = 0x6D;
static const uint16_t ATM90E36_REGISTER_IOFFSETN = 0x6E;
static const uint16_t ATM90E36_REGISTER_CS3 = 0x6F;

static const uint16_t ATM90E36_REGISTER_APENERGY = 0x81;
static const uint16_t ATM90E36_REGISTER_ANENERGY = 0x85;
static const uint16_t ATM90E36_REGISTER_PMEAN = 0xB1;
static const uint16_t ATM90E36_REGISTER_QMEAN = 0xB5;
static const uint16_t ATM90E36_REGISTER_SMEANA = 0xB9;
static const uint16_t ATM90E36_REGISTER_PFMEAN = 0xBD;
static const uint16_t ATM90E36_REGISTER_URMS = 0xD5;
static const uint16_t ATM90E36_REGISTER_IRMSN = 0xD8;
static const uint16_t ATM90E36_REGISTER_IRMS = 0xDD;
static const uint16_t ATM90E36_REGISTER_PMEANH = 0xC9;
static const uint16_t ATM90E36_REGISTER_PANGLE = 0xC4;
static const uint16_t ATM90E36_REGISTER_IPEAK = 0xE8;
static const uint16_t ATM90E36_REGISTER_FREQ = 0xF8;
static const uint16_t ATM90E36_REGISTER_TEMP = 0xF9;

}  // namespace atm90e36
}  // namespace esphome
