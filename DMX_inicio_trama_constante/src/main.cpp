#include <Arduino.h>

long previousMillis = 0;
long currentMillis = 0;




void setup() {
  //Serial.begin(9600);
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
}

void loop() {

  /*Trama Constante con delay*/

  digitalWrite(2, LOW);
  delayMicroseconds(2);
  digitalWrite(2, HIGH);
  delayMicroseconds(10);
  digitalWrite(2, LOW);
  delayMicroseconds(2);
  digitalWrite(2, HIGH);
  delayMicroseconds(2);
  digitalWrite(2, LOW);
  delayMicroseconds(14);
  digitalWrite(2, HIGH);
  delayMicroseconds(22);
  digitalWrite(2, LOW);
  delayMicroseconds(10);
  digitalWrite(2, HIGH);
  delayMicroseconds(18);
  digitalWrite(2, LOW);
  delayMicroseconds(2);
  digitalWrite(2, HIGH);
  delayMicroseconds(26);
  digitalWrite(2, LOW);
  delayMicroseconds(2);
  digitalWrite(2, HIGH);
  delayMicroseconds(58);
  digitalWrite(2, LOW);
  /*Canal número 0 disk*/
  delayMicroseconds(34);
  digitalWrite(2, HIGH);
  delayMicroseconds(26);
  digitalWrite(2, LOW);
  /*Canal número 1 disk*/
  delayMicroseconds(34);
  digitalWrite(2, HIGH);
  delayMicroseconds(26);
  digitalWrite(2, LOW);
  /*Canal número 2 disk*/
  delayMicroseconds(34);
  digitalWrite(2, HIGH);
  delayMicroseconds(26);
  digitalWrite(2, LOW);
  /*Canal número 3 disk*/
  delayMicroseconds(34);
  digitalWrite(2, HIGH);
  delayMicroseconds(26);
  digitalWrite(2, LOW);
  /*Canal número 4 disk*/
  //delayMicroseconds(2);
  //digitalWrite(2, HIGH);
  //delayMicroseconds(58);
  //digitalWrite(2, LOW);
  delayMicroseconds(2);
  digitalWrite(2, HIGH);
  delayMicroseconds(58);
  digitalWrite(2, LOW);
  /*Canal número 5 disk*/
  delayMicroseconds(34);
  digitalWrite(2, HIGH);
  delayMicroseconds(26);
  digitalWrite(2, LOW);
  /*Canal número 6 disk*/
  delayMicroseconds(34);
  digitalWrite(2, HIGH);
  delayMicroseconds(26);
  digitalWrite(2, LOW);
  /*Canal número 7 disk*/
  delayMicroseconds(18);
  digitalWrite(2, HIGH);
  delayMicroseconds(2);
  digitalWrite(2, LOW);
  delayMicroseconds(10);
  digitalWrite(2, HIGH);




/*
  for (size_t i = 0; i < largoData; i++) {

    if ( condition ) {
       code
    }
  */



  delay(2000);


  /*Trama Constante con delay*/
 /*
  digitalWrite(2, LOW);
  delayMicroseconds(2);
  digitalWrite(2, HIGH);
  delayMicroseconds(10);
  digitalWrite(2, LOW);
  delayMicroseconds(2);
  digitalWrite(2, HIGH);
  delayMicroseconds(2);
  digitalWrite(2, LOW);
  delayMicroseconds(14);
  digitalWrite(2, HIGH);
  delayMicroseconds(22);
  digitalWrite(2, LOW);
  delayMicroseconds(10);
  digitalWrite(2, HIGH);
  delayMicroseconds(18);
  digitalWrite(2, LOW);
  delayMicroseconds(2);
  digitalWrite(2, HIGH);
  delayMicroseconds(26);
  digitalWrite(2, LOW);
  delayMicroseconds(2);
  digitalWrite(2, HIGH);
  delayMicroseconds(58);
  digitalWrite(2, LOW);
  //Canal número 0 disk
  delayMicroseconds(34);
  digitalWrite(2, HIGH);
  delayMicroseconds(26);
  digitalWrite(2, LOW);
  //Canal número 1 disk
  delayMicroseconds(34);
  digitalWrite(2, HIGH);
  delayMicroseconds(26);
  digitalWrite(2, LOW);
  //Canal número 2 disk
  delayMicroseconds(34);
  digitalWrite(2, HIGH);
  delayMicroseconds(26);
  digitalWrite(2, LOW);
  //Canal número 4 disk
  delayMicroseconds(34);
  digitalWrite(2, HIGH);
  delayMicroseconds(26);
  digitalWrite(2, LOW);
  //Canal número 5 disk
  delayMicroseconds(2);
  digitalWrite(2, HIGH);
  delayMicroseconds(58);
  digitalWrite(2, LOW);
  //Canal número 6 disk
  delayMicroseconds(34);
  digitalWrite(2, HIGH);
  delayMicroseconds(26);
  digitalWrite(2, LOW);
  //Canal número 7 disk
  delayMicroseconds(18);
  digitalWrite(2, HIGH);
  delayMicroseconds(2);
  digitalWrite(2, LOW);
  delayMicroseconds(10);
  digitalWrite(2, HIGH);


  delay(2000);



  digitalWrite(2, LOW);
  delayMicroseconds(2);
  digitalWrite(2, HIGH);
  delayMicroseconds(10);
  digitalWrite(2, LOW);
  delayMicroseconds(2);
  digitalWrite(2, HIGH);
  delayMicroseconds(2);
  digitalWrite(2, LOW);
  delayMicroseconds(14);
  digitalWrite(2, HIGH);
  delayMicroseconds(22);
  digitalWrite(2, LOW);
  delayMicroseconds(10);
  digitalWrite(2, HIGH);
  delayMicroseconds(18);
  digitalWrite(2, LOW);
  delayMicroseconds(2);
  digitalWrite(2, HIGH);
  delayMicroseconds(26);
  digitalWrite(2, LOW);
  delayMicroseconds(2);
  digitalWrite(2, HIGH);
  delayMicroseconds(58);
  digitalWrite(2, LOW);
  //Canal número 0 disk
  delayMicroseconds(34);
  digitalWrite(2, HIGH);
  delayMicroseconds(26);
  digitalWrite(2, LOW);
  //Canal número 1 disk
  delayMicroseconds(34);
  digitalWrite(2, HIGH);
  delayMicroseconds(26);
  digitalWrite(2, LOW);
  //Canal número 2 disk
  delayMicroseconds(34);
  digitalWrite(2, HIGH);
  delayMicroseconds(26);
  digitalWrite(2, LOW);
  //Canal número 3 disk
  delayMicroseconds(34);
  digitalWrite(2, HIGH);
  delayMicroseconds(26);
  digitalWrite(2, LOW);
  //Canal número 4 disk
  delayMicroseconds(34);
  digitalWrite(2, HIGH);
  delayMicroseconds(26);
  digitalWrite(2, LOW);
  //Canal número 5 disk
  delayMicroseconds(34);
  digitalWrite(2, HIGH);
  delayMicroseconds(26);
  digitalWrite(2, LOW);
  //Canal número 6 disk
  delayMicroseconds(2);
  digitalWrite(2, HIGH);
  delayMicroseconds(58);
  digitalWrite(2, LOW);
  //Canal número 7 disk
  delayMicroseconds(18);
  digitalWrite(2, HIGH);
  delayMicroseconds(2);
  digitalWrite(2, LOW);
  delayMicroseconds(10);
  digitalWrite(2, HIGH);


  delay(2000);

  digitalWrite(2, LOW);
  delayMicroseconds(2);
  digitalWrite(2, HIGH);
  delayMicroseconds(10);
  digitalWrite(2, LOW);
  delayMicroseconds(2);
  digitalWrite(2, HIGH);
  delayMicroseconds(2);
  digitalWrite(2, LOW);
  delayMicroseconds(14);
  digitalWrite(2, HIGH);
  delayMicroseconds(22);
  digitalWrite(2, LOW);
  delayMicroseconds(10);
  digitalWrite(2, HIGH);
  delayMicroseconds(18);
  digitalWrite(2, LOW);
  delayMicroseconds(2);
  digitalWrite(2, HIGH);
  delayMicroseconds(26);
  digitalWrite(2, LOW);
  delayMicroseconds(2);
  digitalWrite(2, HIGH);
  delayMicroseconds(58);
  digitalWrite(2, LOW);
  //Canal número 0 disk
  delayMicroseconds(34);
  digitalWrite(2, HIGH);
  delayMicroseconds(26);
  digitalWrite(2, LOW);
  //Canal número 1 disk
  delayMicroseconds(34);
  digitalWrite(2, HIGH);
  delayMicroseconds(26);
  digitalWrite(2, LOW);
  //Canal número 2 disk
  delayMicroseconds(34);
  digitalWrite(2, HIGH);
  delayMicroseconds(26);
  digitalWrite(2, LOW);
  //Canal número 3 disk
  delayMicroseconds(2);
  digitalWrite(2, HIGH);
  delayMicroseconds(58);
  digitalWrite(2, LOW);
  //Canal número 4 disk
  delayMicroseconds(34);
  digitalWrite(2, HIGH);
  delayMicroseconds(26);
  digitalWrite(2, LOW);
  //Canal número 5 disk
  delayMicroseconds(34);
  digitalWrite(2, HIGH);
  delayMicroseconds(26);
  digitalWrite(2, LOW);
  //Canal número 6 disk
  delayMicroseconds(34);
  digitalWrite(2, HIGH);
  delayMicroseconds(26);
  digitalWrite(2, LOW);
  //Canal número 7 disk
  delayMicroseconds(18);
  digitalWrite(2, HIGH);
  delayMicroseconds(2);
  digitalWrite(2, LOW);
  delayMicroseconds(10);
  digitalWrite(2, HIGH);

  delay(2000);
*/



}
