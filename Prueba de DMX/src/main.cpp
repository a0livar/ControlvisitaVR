// - - - - -
// DmxSerial - A hardware supported interface to DMX.
// DMXSerialFlow.ino: Sample DMX application for sending 60 DMX values.
// Copyright (c) 2014-2015 by Matthias Hertel, http://www.mathertel.de
// This work is licensed under a BSD style license. See http://www.mathertel.de/License.aspx
//
// Documentation and samples are available at http://www.mathertel.de/Arduino
// 25.07.2011 creation of the DmxSerial library.
// 01.07.2013 published version of the example applikation
//
// This is an example of how to send a more complex RGB based pattern of colors
// over a DMX line.
// The values for one of the channels can be watched at the PWM outputs of the Arduino Board.
// - - - - -
#include <Arduino.h>
#include <DMXSerial.h>

// Constants for demo program

unsigned long currentMillis = 0;
unsigned long previousMillis = 0;
uint16_t tiempo = 1000;
uint8_t n = 5;

uint8_t max_canal = 9;

#define PIXELS 12

void setup(void)
{
DMXSerial.init(DMXController);

DMXSerial.write(1, 255);
DMXSerial.write(9, 255);


currentMillis = millis();
} // setup



void loop(void)
{
  currentMillis = millis();

  if (currentMillis - previousMillis  > tiempo) {


    if (n == 5) {
      DMXSerial.write(n, 255);
      DMXSerial.write(8, 0);
    }
    else{
      DMXSerial.write(n, 255);
      DMXSerial.write(n-1, 0);
    }

    if (n >= max_canal-1) {
      //DMXSerial.write(5, 255);
      //DMXSerial.write(6, 255);
      //DMXSerial.write(7, 255);
      n = 4;
    }

    n = n+1;


    previousMillis = currentMillis;
  }

  // create some DMX test values: 5 RGB channels
  // adjust the "12" for changing the speed
  //int alpha = (now / 12) % 765;

  // uncomment this line to have a scenario where DMX values are changed ~ 2 times the second
  // alpha = (alpha / 64) * 64;
  // uncomment this line to have a scenario where DMX values are changed every 5 seconds
  // alpha &= 0xFF00;

  //for (int n = 0; n < PIXELS; n++) {
  //  DMXSerial.write(n, hue-255);
  //} // for


}

// End
