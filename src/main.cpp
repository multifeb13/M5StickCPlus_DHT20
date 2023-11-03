#include <M5StickCPlus.h>
#include <Wire.h>

#include "DHT20.hpp"

TFT_eSprite sprite(&M5.Lcd);
DHT20 dht20(32, 33);

void setup() {
  M5.begin();

  M5.Lcd.setRotation(1);
  sprite.createSprite(M5.Lcd.width(), M5.Lcd.height());
}

void loop() {
  delay(500);

  float tp;
  float hu;
  dht20.read(tp, hu);

  sprite.fillScreen(BLACK);
  sprite.drawString("T=" + String(tp) + "'C", 0, 30, 4);
  sprite.drawString("H=" + String(hu) + "%", 0, 60, 4);
  sprite.pushSprite(0, 0);
}