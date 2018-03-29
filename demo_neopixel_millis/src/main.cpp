#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define PIN_SEC_1 10
#define PIN_SEC_2 11
#define NUMPIXELS 344
//#define NUMPIXELS 20

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN_SEC_1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels2 = Adafruit_NeoPixel(NUMPIXELS, PIN_SEC_2, NEO_GRB + NEO_KHZ800);


unsigned long currentMillis = 0;
unsigned long previousMillis = 0;

unsigned int delay_millis = 100;
uint8_t i = 0, j = 0;
bool estado = false;
uint8_t efect=11;
uint16_t pixcel = 0;
uint16_t ancho = 3;
uint8_t nr=0;
uint8_t ng=0xff;
uint8_t nb=0xff;

uint32_t Wheel(byte);
void allColor(byte,byte,byte);
void setup() {
    Serial.begin(9600);
  pixels.begin();
  pixels.show();
  pixels2.begin();
  pixels2.show();
  previousMillis = currentMillis;
}

void loop() {
  while (Serial.available()){
     //Serial.print("llego");
     efect = Serial.read();
     Serial.print(efect);
     if (efect == 12){
        pixcel = 0;
        ancho = 3;
        nr = 0;
        ng = 0xff;
        nb = 0xff;
    }
  }
  currentMillis = millis();
  if ((currentMillis - previousMillis) > delay_millis){
      currentMillis = millis();
      previousMillis = currentMillis;
    switch (efect){
        case 10 :{
            //Serial.print("Zero");
            allColor(0x00,0x00,0x00);
            pixels.show();
            pixels2.show();
        }break;
        case 11 :{
            //Serial.print("Uno");
            allColor(0xff,0xff,0xff);
            pixels.show();
            pixels2.show();
        }break;
        case 12 : {
            //Serial.print("Dos");
            // pixcel avanzando
            for (uint32_t i=0;i<NUMPIXELS;i++){
                if (i >= pixcel  && i <= (pixcel+ancho)){
                    pixels.setPixelColor(i, nr, ng, nb);
                    pixels2.setPixelColor(i, nr, ng, nb);
                }else{
                    pixels.setPixelColor(i, 0, 0, 0);
                    pixels2.setPixelColor(i, 0, 0, 0);
                }
            }
            pixcel ++;
            if (pixcel > NUMPIXELS){
                pixcel = 0;
                delay_millis = delay_millis - 10;
            }
            if (delay_millis <= 10)
            {
                delay_millis = 100;
            }
            pixels.show();
            pixels2.show();
        }
    }
  }

}

void allColor(byte r,byte g,byte b){
  for (uint32_t i=0;i<NUMPIXELS;i++){
      pixels.setPixelColor(i, r,g,b);
      pixels2.setPixelColor(i, r,g,b);
  }
  pixels.show();
  pixels2.show();
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
