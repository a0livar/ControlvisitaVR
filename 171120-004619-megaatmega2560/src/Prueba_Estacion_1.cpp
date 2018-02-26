

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <CircularBuffer.h> //Buffer Circular

/******

Definición de protocolo

AA01016400FF
AA = Inicio de paquete
01 = Tipo
01 = Canal
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

//Pinout tipo 1
#define PIN_PWM_1 10
#define PIN_PWM_2 11

//Pinout tipo 2
#define SECUENCIAL_1 2


int i = 0;
int tipo = 0, valor = 0, tiemp = 0, aux_val = 0;
char byteIN[4]="\0";
byte NEXTbyte = 0x00;
boolean run = false;

CircularBuffer<char, 10> buffer;

void setup() {
 Serial.begin(9600);
 //Serial1.begin(9600);

 pinMode(SECUENCIAL_1, OUTPUT);
 pinMode(PIN_PWM_1);
 pinMode(PIN_PWM_2);

}

void loop() {


  if(run){
    Serial.print("llego byte");
    for(i=0;i<4;i++){
      Serial.print(byteIN[i]);
    }
  tipo = (int)byteIN[0];
  canal = (int)byteIN[1];
  valor = (int)byteIN[2];

  switch (tipo) {
    case 1:
    if (canal == 1) {
      analogWrite(PIN_PWM_1, valor*255/100);
    }
    if (canal == 2) {
      analogWrite(PIN_PWM_2, (valor*255)/100);
    }
    case 2:
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
  aux_val = valor;
  }//fin run


  //delay(10);
delay(20);


run = false;
memset(byteIN, 0, sizeof(byteIN));
NEXTbyte = 0x00;
}

void serialEvent1()
{
  while(Serial1.available())
  {
    byte inChar = (byte)Serial1.read();
    Serial.print(inChar);
    if(inChar == 0xFF)
    {
    run = true;
    Serial.println("");
    }

    else
    {
      byteIN[NEXTbyte]= inChar;
      NEXTbyte++;
    }
  }
}
