#pragma once

#include <Wire.h>

#include "DHT20.hpp"

class DHT20 {
 public:
  DHT20();                              // for M5Stack
  DHT20(const int sda, const int sdl);  // for M5StickC/CPlus

  void read(float& temperature, float& humidity);

 private:
  const int i2c_adr_ = 0x38;
  const int data_bytes_ = 6;
};