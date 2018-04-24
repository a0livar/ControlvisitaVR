#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <avr/wdt.h>

#define PIN_SEC_1 10
#define NUMPIXELS 512

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN_SEC_1, NEO_GRB + NEO_KHZ800);

unsigned long currentMillis = 0;
unsigned long previousMillis = 0;

unsigned int delay_millis = 20;
uint8_t i = 0, j = 0;
uint16_t i2, j2;
bool estado = false;
bool ok = false;
bool dowork = true;
uint8_t efect=255;
uint8_t tmpEfect=255;

uint16_t pixcel = 0;
uint16_t ancho = 3;
uint8_t nr=0;
uint8_t ng=0xff;
uint8_t nb=0xff;

uint8_t read = 0;
uint8_t head = 0;
uint8_t r = 0xff;
uint8_t g = 0xff;
uint8_t b = 0xff;

const unsigned int LARGO = 0xFF;
int escribe = 0;
int estadoSerial = 1;
int estadoProtocolo = 1;
int lee = 0;
int largoData = 0;
byte data[LARGO +1] = "\0";

uint32_t Wheel(byte);
void allColor(byte,byte,byte);
int distancia(void);
void incrementaLee(void);
void incrementaEscribe(void);
//void leeFunction(void);
void escribeFunction(void);

void setup() {
   Serial.begin(9600);
   pixels.begin();
   pixels.show();
   previousMillis = currentMillis;
   //wdt_disable();
   wdt_enable(WDTO_1S);
   Serial.print("Init");
}

void serialEvent(){
    if(Serial.available() == 3)
    {
        //tmpEfect = Serial.read();
        r = Serial.read();
        g = Serial.read();
        b = Serial.read();

        if (r == 1){
            tmpEfect = 21;
            pixcel = 0;
            ancho = 10;
            nr = 0;
            ng = 0xff;
            nb = 0xff;
        }else{
            tmpEfect = 255;
        }
    }
    if (Serial.available() > 3){
        Serial.flush();
    }
}
void loop() {
  wdt_reset();

    if (tmpEfect == 255){
        efect = 255;
    }
    if (tmpEfect == 21){
        efect = 21;
    }

  currentMillis = millis();
  if ((currentMillis - previousMillis) > delay_millis){
      wdt_reset();
      Serial.print(r);
      Serial.print(g);
      Serial.println(b);

      currentMillis = millis();
      previousMillis = currentMillis;
      j2 = j2 +1;
      if (j2 >= 1000){
          j2 = 0;
      }
    switch (efect){

        case 21:{
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
      delay_millis = delay_millis - 2;
  }
  if (delay_millis <= 2)
  {
      delay_millis = 20;
  }
  pixels.show();

        }break;

        case 255:{
            Serial.print("RGB");
            allColor(r,g,b);
            pixels.show();
        }break;
    }
  }

}

void allColor(byte lr,byte lg,byte lb){
  for (uint32_t i=0;i<NUMPIXELS;i++){
      pixels.setPixelColor(i, lr,lg,lb);
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

int distancia(){
  if (lee == escribe){
    return 0;
    }
  if (lee < escribe){
    return escribe - lee;
  }else
  {
      return ((LARGO - lee) + escribe + 1);
    }
}
void incrementaLee(){
    lee++;
    lee &= LARGO;
}
void incrementaEscribe(){
    escribe++;
    escribe &= LARGO;
  }
  void escribeFunction(){
      data[escribe] = (byte) Serial.read();
      //Serial.write(data[escribe]);
     incrementaEscribe();
  }
