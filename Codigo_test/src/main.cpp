#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <CircularBuffer.h>
#include <stdlib.h>
#include <string.h>


/******

Definición de protocolo

AA01016400FF
AA = Inicio de paquete
01 = Tipo
01 = Canal
01 = Funcion
64 = Valor
00 = Tiempo
FF = Cierre de paquete

Tipo
1 = Dimmer corriente continua
2 = Dimmer corriente alterna
3 = Secuencia
4 = DMX

Valor
0 -> 100

*******/


#define NUMPIXELS 300//numero de pixeles led secuencial

//Pinout tipo 1
#define PIN_PWM_1 10
#define PIN_PWM_2 11

//Pinout tipo 2
#define PIN_SEC_1 2

CircularBuffer<byte, 10> buffer;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN_SEC_1, NEO_GRB + NEO_KHZ800);


unsigned long currentMillis = 0;
unsigned long previousMillis = 0;

unsigned int delay_millis = 1;
uint8_t tipo = 0, canal = 0, valor = 0, tiempo = 0;
uint8_t i = 0, j = 0;
uint8_t aa = 0x00;

uint32_t Wheel(byte);

void setup() {
  pixels.begin();
  pixels.show();
  Serial.begin(9600);

  pinMode(PIN_SEC_1, OUTPUT);
  pinMode(PIN_PWM_1, OUTPUT);
  pinMode(PIN_PWM_2, OUTPUT);

  previousMillis = currentMillis;
}

void loop() {

  currentMillis = millis();
  if (currentMillis - previousMillis > delay_millis) {//Funcion 1 sobre leds secuenciales
    pixels.setPixelColor(i, Wheel((i+j) & 255));
    pixels.show();
    if (i == NUMPIXELS - 1) {
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

  if(buffer.size() == 5){

    pixels.setPixelColor(5, pixels.Color(0,0,255));
    pixels.show();
    analogWrite(PIN_PWM_1, 127);
    //Serial.print("A80");
    Serial.println(buffer.shift());
    Serial.print(buffer.shift());
    Serial.print(buffer.shift());
    Serial.print(buffer.shift());
    Serial.print(buffer.shift());
    //Serial.print("llego byte");
  //aa      = (int) buffer.shift();
  //tipo    = (int) buffer.shift();
  //canal   = (int) buffer.shift();
  //valor   = (int) buffer.shift();
  //tiempo  = (int) buffer.shift();

  switch (tipo) {
    case 1:
    if (canal == 1) {
      analogWrite(PIN_PWM_1, valor*255/100);
    }
    if (canal == 2) {
      analogWrite(PIN_PWM_2, (valor*255)/100);
    }
    case 2:
    if (canal == 1) {
      if (valor<100) {
        char buffer_valor[4] = " ";
        sprintf(buffer_valor, "A0%d",valor);
        Serial.print(buffer_valor);
      }
      else{
        char buffer_valor[4] = " ";
        sprintf(buffer_valor, "A%d",valor);
        Serial.print(buffer_valor);
    }
    }
    if (canal == 2) {
      if (valor<100) {
        char buffer_valor[4] = " ";
        sprintf(buffer_valor, "B0%d",valor);
        Serial.print(buffer_valor);
      }
      else{
        char buffer_valor[4] = " ";
        sprintf(buffer_valor, "B%d",valor);
        Serial.print(buffer_valor);
    }
    }

  }buffer.clear();
}//fin run




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

  //run = false;
  //buffer.clear();
  //aa = 0x00;
}


void serialEvent(){
  while(Serial.available()>0)
  {
    buffer.push((byte) Serial.read());
  }
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
