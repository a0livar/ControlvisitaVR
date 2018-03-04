#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define PIN_SEC_1 2
#define NUMPIXELS 300

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN_SEC_1, NEO_GRB + NEO_KHZ800);

int delayval = 5;

void setup() {
  pixels.begin();
}

void loop() {
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(165,165,165));
    pixels.show();
    delay(delayval);
  }
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0,0,0));
    pixels.show();
    delay(delayval);
  }
}
