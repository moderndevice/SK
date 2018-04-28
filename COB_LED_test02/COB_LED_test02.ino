/*
  Fading

  This example shows how to fade an LED using the analogWrite() function.

  The circuit:
  - LED attached from digital pin 9 to ground.

  created 1 Nov 2008
  by David A. Mellis
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Fading
*/

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>
#include "colorFunctions.h"

Adafruit_LIS3DH lis = Adafruit_LIS3DH();

int whitePin = 11;    // LED connected to digital pin 9
int bluePin = 10;    // LED connected to digital pin 9
int greenPin = 9;    // LED connected to digital pin 9
int redPin = 5;    // LED connected to digital pin 9

uint8_t white, red, green, blue;


// #define DEBUG_ACCEL
 #define DEBUG_COLOR

void setup() {
  // nothing happens in setup
  pinMode(whitePin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  Serial.begin(9600);
  Serial.println("LIS3DH test!");

  if (! lis.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1);
  }
  Serial.println("LIS3DH found!");
  lis.setRange(LIS3DH_RANGE_4_G);   // 2, 4, 8 or 16 G!

}

void loop() {

  //digitalWrite(whitePin, HIGH);
  //digitalWrite(redPin, HIGH);
  //digitalWrite(greenPin, HIGH);
  //digitalWrite(bluePin, HIGH);
  //
  //delay(20);
  //digitalWrite(whitePin, LOW);
  //digitalWrite(redPin, LOW);
  //digitalWrite(greenPin, LOW);
  //digitalWrite(bluePin, LOW);
  //
  //
  //delay(200);
  //



  lis.read();      // get X Y and Z data at once
  // Then print out the raw data
  //  Serial.print("X:  "); Serial.print(lis.x);
  //  Serial.print("  \tY:  "); Serial.print(lis.y);
  //  Serial.print("  \tZ:  "); Serial.println(lis.z);

  float x = lis.x ;
  float y = lis.y ;
  float z = lis.z ;

  float  tiltx = atan2(x, sqrt((y * y) + (z * z)));
  float tilty = atan2(y, sqrt((x * x) + (z * z)));
  float  tiltz = atan2(z, sqrt((y * y) + (x * x)));
  float  angle = atan2(tilty, tiltx);

#ifdef DEBUG_ACCEL

  Serial.print(" tiltx  "); Serial.print(tiltx);
  Serial.print("  \ttilty  "); Serial.print(tilty);
  Serial.print("  \ttiltz  "); Serial.print(tiltz);
  Serial.print("  \tangle  "); Serial.println(angle);

#endif

  int angle2 = (angle + 3.14) * 255.0 / (2 * PI);


  int sat = constrain (((abs(tiltx)*3 + abs(tilty)*3) * 255), 0, 255);
  uint32_t color = HSV(angle2, sat, 255);
  white = color >> 24;
  red = color >> 16;
  green = color >> 8;
  blue = color;


  analogWrite(whitePin, white);
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);

#ifdef DEBUG_COLOR
  Serial.print("  \tangle2  "); Serial.print(angle2);
    Serial.print("  \tsat  "); Serial.print(sat);
  Serial.print(" white  "); Serial.print(white);
  Serial.print(" red  "); Serial.print(red);
  Serial.print("  green  "); Serial.print(green);
  Serial.print("  blue  "); Serial.println(blue);

#endif



}

