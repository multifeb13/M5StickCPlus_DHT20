#include <M5StickCPlus.h>
#include <Wire.h>
#define ADR 0x38

TFT_eSprite sprite(&M5.Lcd);

void setup() {
  M5.begin();
  Wire.begin(32, 33);

  M5.Lcd.setRotation(1);
  sprite.createSprite(M5.Lcd.width(), M5.Lcd.height());
}

void loop() {
  uint8_t buf[8] = {0};

  delay(500);

  do {
    Wire.beginTransmission(ADR);
    Wire.write(0xac);
    Wire.write(0x33);
    Wire.write(0x00);
    Wire.endTransmission();
    delay(100);

    Wire.requestFrom(ADR, 6);
    for (uint8_t i = 0; i < 6; i++) {
      buf[i] = Wire.read();
    }
  } while (buf[0] & 0x80);

  long a;
  a = buf[1];
  a <<= 8;
  a |= buf[2];
  a <<= 4;
  a |= ((buf[3] >> 4) & 0x0f);
  float hu = a / 10485.76;

  a = (buf[3] & 0xf);
  a <<= 8;
  a |= buf[4];
  a <<= 8;
  a |= buf[5];
  float tp = a / 5242.88 - 50;

  sprite.fillScreen(BLACK);
  sprite.drawString("T=" + String(tp) + "'C ", 0, 30, 4);
  sprite.drawString("H=" + String(hu) + "%", 0, 60, 4);
  sprite.pushSprite(0, 0);
}