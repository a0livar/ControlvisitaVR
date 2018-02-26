#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <CircularBuffer.h>


#define NUMPIXELS 12//numero de pixeles led secuencial

//Pinout tipo 1
#define PIN_PWM_1 10
#define PIN_PWM_2 11

//Pinout tipo 2
#define PIN_SEC_1 2

CircularBuffer<char, 10> buffer;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN_SEC_1, NEO_GRB + NEO_KHZ800);


unsigned long currentMillis = 0;
unsigned long previousMillis = 0;

unsigned int delay_millis = 1;
uint8_t tipo = 0, canal = 0, valor = 0, tiempo = 0;
uint8_t i = 0, j = 0;
bool estado = false;
bool run = false;

uint32_t Wheel(byte);

void setup() {
  pixels.begin();
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

  if(run){
    //Serial.print("llego byte");
  tipo = buffer.shift();
  canal = buffer.shift();
  valor = buffer.shift();
  tiempo = buffer.shift();

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

  }

  /*if (valor>aux_val) {
    for(i=aux_val;i<=valor;i++){
      analogWrite(9, i);
    }
  }
  else{
    for(i=aux_val;i>=valor;i--){
    analogWrite(9, i);
    }
  }*/
  //aux_val = valor;
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

  run = false;

}

void serialEvent()
{
  while(Serial.available())
  {
    byte inChar = (byte)Serial.read();
    //Serial.print(inChar);
    if(inChar == 0xFF)
    {
    run = true;
    //Serial.println("");
    }

    else
    {
      buffer.push(inChar);
    }
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
