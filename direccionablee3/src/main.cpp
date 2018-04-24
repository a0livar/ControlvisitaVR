#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define PIN_SEC_1 10
#define NUMPIXELS 512

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN_SEC_1, NEO_GRB + NEO_KHZ800);

unsigned long currentMillis = 0;
unsigned long previousMillis = 0;

unsigned int delay_millis = 50;
uint8_t i = 0, j = 0;
bool estado = false;
uint8_t efect=10;
uint8_t tmpEfect=10;

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
   previousMillis = currentMillis;
}

void loop() {
  while (Serial.available()){
     Serial.print("llego");
     tmpEfect = Serial.read();
     if ((tmpEfect >= 10) && (tmpEfect <= 20)){
         efect = tmpEfect;
     }
     // Estación 4-> 10 - 20
     Serial.print(efect);

     //prepara el efecto 20
     if (efect == 20){
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

        }break;
        case 11 :{
            //Serial.print("Uno");
            allColor(0xff,0xff,0xff);
            pixels.show();

        }break;
        case 12 :{
            //Serial.print("Uno");
            allColor(241,98,26);
            pixels.show();

        }break;
        case 13 :{
            //Serial.print("Uno");
            allColor(70,159,10 );
            pixels.show();

        }break;
        case 14 :{
            //Serial.print("Uno");
            allColor(217,200,35 );
            pixels.show();

        }break;
        case 15 :{
            //Serial.print("Uno");
            allColor(180,0,234 );
            pixels.show();

        }break;
        case 16 :{
            //Serial.print("Uno");
            allColor(34,150,181);
            pixels.show();

        }break;
        case 17 :{
            //Serial.print("Uno");
            allColor(179,89,5);
            pixels.show();
        }break;

        case 20 : {
            //Serial.print("Dos");
            //pixcel avanzando
            for (uint32_t i=0;i<NUMPIXELS;i++){
                if (i >= pixcel  && i <= (pixcel+ancho)){
                    pixels.setPixelColor(i, nr, ng, nb);

                }else{
                    pixels.setPixelColor(i, 0, 0, 0);

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
        }
    }
  }

}

void allColor(byte r,byte g,byte b){
  for (uint32_t i=0;i<NUMPIXELS;i++){
      pixels.setPixelColor(i, r,g,b);
  }
  pixels.show();
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
