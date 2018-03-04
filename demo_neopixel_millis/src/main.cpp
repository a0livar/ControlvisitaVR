#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define PIN_SEC_1 2
#define NUMPIXELS 344

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN_SEC_1, NEO_GRB + NEO_KHZ800);


unsigned long currentMillis = 0;
unsigned long previousMillis = 0;

unsigned int delay_millis = 1;
uint8_t i = 0, j = 0;
bool estado = false;

uint32_t Wheel(byte);

void setup() {
  pixels.begin();
  previousMillis = currentMillis;
}

void loop() {

  currentMillis = millis();
  if (currentMillis - previousMillis > delay_millis) {
    pixels.setPixelColor(i, Wheel((i+j) & 255));
    pixels.show();
    if (i == NUMPIXELS) {
      i = 0;
      j++;
    }
    else i++;
    if (j == 255) {
      j = 0;
      //estado = true;
    }
    previousMillis = currentMillis;
  }


  /*if (currentMillis - previousMillis > delay_millis && estado == true) {
    pixels.setPixelColor(i, pixels.Color(0,0,0));
    pixels.show();
    if (i == 0) {
      i = 0;
      estado = false;
    }
    else i--;
    previousMillis = currentMillis;
  }*/

  /*
  if (currentMillis - previousMillis > 10) {
    pixels.setPixelColor(6, pixels.Color(i*20,0,0));
    pixels.show();
  }*/

}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
