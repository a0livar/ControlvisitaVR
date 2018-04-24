#include <Arduino.h>
//#include <DMXSerial.h>
unsigned long currentMillis = 0;
unsigned long lastserialMillis = 0;

char cadenaRX[7] =   "\0";       // Cadena para guardar los diferentes comandos.
boolean comandoCompleto = false;  // Bandera que muestra cuando se termina de
boolean tiempomayorCien = false;
                                  // recibir un comando.
byte  NEXT_char=0x00;             // Contador de datos entrantes desde la USART.

void setup() {
    Serial.begin(9600);
    //DMXSerial.init(DMXController);
    //DMXSerial.write(1, 255); //Seteamos el control dimmer a su maximo nivel
    //DMXSerial.write(9, 255); //Seteamos el control dimmer a su maximo nivel
    memset(cadenaRX, 0, sizeof(cadenaRX));
    currentMillis = millis();
}

void loop() {
    currentMillis = millis();
    // put your main code here, to run repeatedly:
    if (comandoCompleto && tiempomayorCien) {
    //DMXSerial.write(5, cadenaRX[0]);
    //DMXSerial.write(6, cadenaRX[1]);
    //DMXSerial.write(7, cadenaRX[2]);
    //DMXSerial.write(13, cadenaRX[3]);
    //DMXSerial.write(14, cadenaRX[4]);
    //DMXSerial.write(15, cadenaRX[5]);

    Serial.write(cadenaRX[0]);
    Serial.write(cadenaRX[1]);
    Serial.write(cadenaRX[2]);
    Serial.write(cadenaRX[3]);
    Serial.write(cadenaRX[4]);
    Serial.write(cadenaRX[5]);

      comandoCompleto = false;
      tiempomayorCien = false;
      memset(cadenaRX, 0, sizeof(cadenaRX));
      NEXT_char=0x00;
      Serial.flush();
    }

    if ((currentMillis - lastserialMillis) > 100) {
      comandoCompleto = false;
      memset(cadenaRX, 0, sizeof(cadenaRX));
      NEXT_char = 0x00;
      Serial.flush();
      lastserialMillis = currentMillis;
      tiempomayorCien = true;
    }


  }


void serialEvent() {
  while(Serial.available()){ // Si el puerto está listo para recibir datos..
  lastserialMillis = millis();
  // Tomamos los datos entrantes.
  char inChar = (char)Serial.read();
    // Guardamos los datos en una cadena.
    cadenaRX[NEXT_char] = inChar;
    NEXT_char++;
    if(NEXT_char==6){
      NEXT_char=0x00;
      comandoCompleto = true;
      Serial.flush();
   }
  }
}
