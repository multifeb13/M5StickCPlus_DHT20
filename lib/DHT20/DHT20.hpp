#pragma once

#include <Wire.h>

#include "DHT20.hpp"

class DHT20 {
 public:
  DHT20();
  void read(float& temperature, float& humidity);

 private:
  const int i2c_sda_ = 32;
  const int i2c_scl_ = 33;
  const int i2c_adr_ = 0x38;
  const int data_bytes_ = 6;
};