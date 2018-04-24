#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <avr/wdt.h>

#define PIN_SEC_1 10
#define NUMPIXELS 512

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN_SEC_1, NEO_GRB + NEO_KHZ800);

unsigned long currentMillis = 0;
unsigned long previousMillis = 0;

unsigned int delay_millis = 50;
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
    //Serial.print(Serial.available());
    //Serial.print(Serial.read());
    if(Serial.available() == 3)
    {
        //tmpEfect = Serial.read();
        r = Serial.read();
        g = Serial.read();
        b = Serial.read();

        if (r == 1){
            tmpEfect = 21;
            pixcel = 0;
            ancho = 3;
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
    //Serial.print(Serial.available());
    /*if (Serial.available() >= 5){
        //data[escribe] = Serial.read();
        head = Serial.read();
        tmpEfect = Serial.read();
        if (head != 0xAA){
            Serial.print("Sin cabecera");
            Serial.flush();
            tmpEfect = efect;
        }else{
            Serial.print("cabecera");
            efect = tmpEfect;
            r = Serial.read();
            g = Serial.read();
            b = Serial.read();
        }

        //Serial.flush();
        //Serial.print(tmpEfect);
        Serial.print(r);
        Serial.print(g);
        Serial.print(b);
        Serial.print("[");
        Serial.print(efect);
        Serial.print("]");

        //incrementaEscribe();
        //escribeFunction();
    }*/


    if (tmpEfect == 255){
        efect = 255;
    }
    if (tmpEfect == 21){
        efect = 21;
    }

    // Serial.print("llego");
     //tmpEfect = Serial.read();
    /* if ((tmpEfect >= 10) && (tmpEfect <= 22)){
         efect = tmpEfect;
     }*/

     // Estación 4-> 10 - 20
     //Serial.print(efect);



  currentMillis = millis();
  if ((currentMillis - previousMillis) > delay_millis){
      wdt_reset();
      Serial.print(r);
      Serial.print(g);
      Serial.println(b);
      /*while(1){
          Serial.print("Q");
      }*/
      currentMillis = millis();
      previousMillis = currentMillis;
      j2 = j2 +1;
      if (j2 >= 1000){
          j2 = 0;
      }
    switch (efect){
        case 10 :{
            Serial.print("Zero");
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
            Serial.print("EF");
            Serial.print(pixcel);
            Serial.print("-");
            Serial.print(pixcel+ancho);
            //pixcel avanzando
            for (uint32_t i=0;i<NUMPIXELS;i++){
                if (i >= pixcel  && i <= (pixcel+ancho)){
                    pixels.setPixelColor(i, nr, ng, nb);

                }else{
                    pixels.setPixelColor(i, 0, 0, 0);
                }
            }
            pixcel = pixcel +1;
            pixels.show();
            if (pixcel > NUMPIXELS){
                pixcel = 0;
                delay_millis = delay_millis - 10;
            }
            if (delay_millis <= 10)
            {
                delay_millis = 100;
            }
            //pixels.show();
        }break;
        case 21:{
          /*uint16_t i2;
            unsigned long currentMillis2 = millis();
            unsigned long previous2 = millis();
                Serial.println("arc");
                dowork = 1;
                //Serial.println("salio");
                do{
                  if (dowork){
                      for(i2=0; i2< pixels.numPixels(); i2++) {
                        pixels.setPixelColor(i2, Wheel(((i2 * 256 / pixels.numPixels()) + j2) & 255));
                      }
                      dowork = 0;
                    pixels.show();

                   }
                  //delay(wait);
                  currentMillis2 = millis();
              }while(currentMillis2 - previous2 < 20);
          */
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
      delay_millis = delay_millis - 2;
  }
  if (delay_millis <= 2)
  {
      delay_millis = 20;
  }
  pixels.show();

        }break;
        case 22:{
            uint16_t i, j;
            unsigned long currentMillis2 = millis();
            unsigned long previous2 = millis();
            int dowork = 1;

            for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
              currentMillis2 = millis();
              previous2 = millis();
              dowork = 1;
              //Serial.println("salio");
              do{
                if (dowork){
                    for(i=0; i< pixels.numPixels(); i++) {
                      pixels.setPixelColor(i, Wheel(((i * 256 / pixels.numPixels()) + j) & 255));
                    }
                    dowork = 0;
                  pixels.show();

                 }
                //delay(wait);
                currentMillis2 = millis();
            }while(currentMillis2 - previous2 < 20);
            }
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


  /*void leeFunction(){
          if(estadoSerial ==1){
              if (data[lee] == 0xAA){
                  estadoSerial = 2;
                  Serial.print("Estado 2");
                  //toSend[0] = 0xAA;
              }else{
                  Serial.print("Estado 1");
                  estadoSerial = 1;
              }
              incrementaLee();
          }
          if (estadoSerial == 2){
              estadoSerial = 1;
            tmpEfect = data[lee];
           // toSend[1] = tipo;
            incrementaLee();
            r = data[lee];
            incrementaLee();
            g = data[lee];

            incrementaLee();
            b = data[lee];
            incrementaLee();


              if ((tmpEfect >= 10) && (tmpEfect <= 20)){
                  Serial.print("Unit ");
                  efect = tmpEfect;
              }
              if (tmpEfect == 0xff){
                  Serial.print("RGB ");
                  efect = tmpEfect;
              }

              if (efect == 20){
                 pixcel = 0;
                 ancho = 3;
                 nr = 0;
                 ng = 0xff;
                 nb = 0xff;
             }
          }
  }*/
