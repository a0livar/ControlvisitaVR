#include <Arduino.h>

int i = 0;
int channel = 0, valor = 0, tiemp = 0, aux_val = 0;
char byteIN[4]="\0";
byte NEXTbyte = 0x00;
boolean run = false;

void setup() {
 Serial.begin(9600);
 Serial1.begin(9600);

 pinMode(9, OUTPUT);

}

void loop() {


  if(run){
    Serial.print("llego byte");
    for(i=0;i<4;i++){
      Serial.print(byteIN[i]);
    }
  channel = (int)byteIN[0];
  valor = (int)byteIN[1];
  tiemp = (int)byteIN[2];

  if (valor>aux_val) {
    for(i=aux_val;i<=valor;i++){
      analogWrite(9, i);
    }
  }
  else{
    for(i=aux_val;i>=valor;i--){
    analogWrite(9, i);
    }
  }
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
