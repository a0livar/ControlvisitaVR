#include <Arduino.h>
#include <DMXSerial.h>
#include <avr/wdt.h>

unsigned long currentMillis = 0;
unsigned long lastserialMillis = 0;



char cadenaRX[7] =   "\0";       // Cadena para guardar los diferentes comandos.
boolean comandoCompleto = false;  // Bandera que muestra cuando se termina de
boolean tiempomayorCien = false;
                                  // recibir un comando.
byte  NEXT_char=0x00;             // Contador de datos entrantes desde la USART.

void setup() {
    Serial1.begin(9600);
    DMXSerial.init(DMXController);
    DMXSerial.write(1, 255); //Seteamos el control dimmer a su maximo nivel
    DMXSerial.write(9, 255); //Seteamos el control dimmer a su maximo nivel
    memset(cadenaRX, 0, sizeof(cadenaRX));
    currentMillis = millis();
    wdt_disable();
    wdt_enable(WDTO_1S);
}

void loop() {
  currentMillis = millis();
    // put your main code here, to run repeatedly:
    if (comandoCompleto && tiempomayorCien) {
      DMXSerial.write(5, cadenaRX[0]);
      DMXSerial.write(6, cadenaRX[1]);
      DMXSerial.write(7, cadenaRX[2]);
      DMXSerial.write(13, cadenaRX[3]);
      DMXSerial.write(14, cadenaRX[4]);
      DMXSerial.write(15, cadenaRX[5]);

      comandoCompleto = false;
      tiempomayorCien = false;
      memset(cadenaRX, 0, sizeof(cadenaRX));
      NEXT_char=0x00;
      Serial1.flush();
    }

    if ((currentMillis - lastserialMillis) > 100) {
      comandoCompleto = false;
      memset(cadenaRX, 0, sizeof(cadenaRX));
      NEXT_char = 0x00;
      Serial1.flush();
      lastserialMillis = currentMillis;
      tiempomayorCien = true;
    }

    wdt_reset();

  }


void serialEvent1() {
  while(Serial1.available()){ // Si el puerto está listo para recibir datos..
  lastserialMillis = millis();
  // Tomamos los datos entrantes.
  char inChar = (char)Serial1.read();
    // Guardamos los datos en una cadena.
    cadenaRX[NEXT_char] = inChar;
    NEXT_char++;
    if(NEXT_char==6){
      NEXT_char=0x00;
      comandoCompleto = true;
      Serial1.flush();
   }
  }
}
