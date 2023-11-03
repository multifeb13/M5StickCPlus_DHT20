#include "DHT20.hpp"

DHT20::DHT20() { Wire.begin(); }
DHT20::DHT20(const int sda, const int sdl) { Wire.begin(sda, sdl); }

void DHT20::read(float& temperature, float& humidity) {
  uint8_t buf[8] = {0};

  do {
    Wire.beginTransmission(i2c_adr_);
    Wire.write(0xac);
    Wire.write(0x33);
    Wire.write(0x00);
    Wire.endTransmission();
    delay(100);

    Wire.requestFrom(i2c_adr_, data_bytes_);
    for (uint8_t i = 0; i < data_bytes_; i++) {
      buf[i] = Wire.read();
    }
  } while (buf[0] & 0x80);

  long data;
  data = buf[1];
  data <<= 8;
  data |= buf[2];
  data <<= 4;
  data |= ((buf[3] >> 4) & 0x0f);
  humidity = data / 10485.76;

  data = (buf[3] & 0xf);
  data <<= 8;
  data |= buf[4];
  data <<= 8;
  data |= buf[5];
  temperature = data / 5242.88 - 50;
}
