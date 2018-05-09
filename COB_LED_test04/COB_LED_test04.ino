/*
  COB_LED code
  Drive COB LEDs using an accelerometer
  Uses some code derived from Adafruit NeoPixel library
*/

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>

#define TILT_THRESH  0.12

Adafruit_LIS3DH lis2 = Adafruit_LIS3DH();
Adafruit_LIS3DH lis3 = Adafruit_LIS3DH();

int pwmPins[] = { 9, 10, 25, 32,     3, 4, 5, 6,    20, 21, 22, 23};
int redPins[] = {9, 6, 23 };
int greenPins[] = { 10, 3, 22};
int bluePins[] = { 25, 4, 21};
int whitePins[] = { 32, 5, 20 };


float accelX1, accelY1, accelZ1, lastX1, lastY1, lastZ1;
float  tiltx1, tilty1, tiltz1, angle1, tiltXY1;

int accelX2, accelY2, accelZ2, lastX2, lastY2, lastZ2, changeX2, changeY2, changeZ2, changeT2;
float  tiltx2, tilty2, tiltz2, angle2, tiltXY2;

int accelX3, accelY3, accelZ3, lastX3, lastY3, lastZ3, changeX3, changeY3, changeZ3, angleG;
float  tiltx3, tilty3, tiltz3, angle3, tiltXY3;

float *angles[] = {&angle1, &angle2, &angle3};
float *tiltXYs[] = {&tiltXY1, &tiltXY2, &tiltXY3};

uint32_t lastActive;

int maxAccelNo;

uint8_t white, red, green, blue;

/******  DEBUGGING / PRINTING ******/
// #define DEBUG_ACCEL_RAW1 // analog accel
// #define DEBUG_ACCEL_RAW2
// #define DEBUG_ACCEL_RAW3

//#define DEBUG_ACCEL_TILT1
//#define DEBUG_ACCEL_TILT2
//#define DEBUG_ACCEL_TILT3

// #define DEBUG_ACCEL_CHANGE
// #define DEBUG_COLOR

#include "colorFunctions.h"
#include "sensorFunctions.h"


void setup() {

  Serial.begin(57600);
  Serial.println("LIS3DH test!");

  if (!lis2.begin(0x19)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    // while (1);
  }
  else {
    Serial.println("LIS3DH #2 found!");
    lis2.setRange(LIS3DH_RANGE_4_G);   // 2, 4, 8 or 16 G!
  }

  if (! lis3.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
  }
  else {
    Serial.println("LIS3DH #3 found!");
    lis3.setRange(LIS3DH_RANGE_4_G);   // 2, 4, 8 or 16 G!
  }

  for (int i = 0; i < 12; i++) {
    analogWrite(pwmPins[i], 0);
  }

  lastActive = millis();

}

void loop() {
  static int changeRaw, change, color, color1, color2, color3;
  uint8_t hue1, hue2, hue3;
  static float sat, value;
  float smoothAngle;
  int angleT;

  readAnalogAccel1();
  readAccel2();
  readAccel3();

  int maxAccel = compareAccel();

  if (maxAccel) { // found an input
    angleG = ((*angles[maxAccel - 1] + 3.14) * 255.0) / (2.0 * 3.14); // map angle to 0-255 for HSV function
    angleG = angleG % 256;



    sat += (*tiltXYs[maxAccel - 1] * 50.0);
    sat = constrain(sat, 0, 255.0);
    value += (*tiltXYs[maxAccel - 1] * 25.0); // value comes up slower than sat
    value = constrain(value, 0, 255.0);

    //   sat -= 1;
    //
    Serial.print( " tiltXY = ");   Serial.print( *tiltXYs[maxAccel - 1] );
    Serial.print( " angle3 = ");   Serial.print( *angles[maxAccel - 1]);
    Serial.print( " maxAccel = ");   Serial.print( maxAccel);
    Serial.print( " \t smoothAngle = ");   Serial.print( smoothAngle);
    Serial.print( " \t angleG = ");   Serial.print( angleG);

    Serial.print( "sat = ");   Serial.print(sat);
    Serial.print( " value ");   Serial.println( value);


    color = HSV(angleG, sat, value);
    setColors(color);
    color1 = color;
    hue1 = hue2 = hue3 = angleG;
  }

  else {

    sat *= 0.999;
    sat = constrain(sat, 0.0, 255.0);
    value *= 0.99;
    value = constrain(value, 0.0, 255.0);
    hue1 += 1;
    hue2 -= 2;
    hue3 -= 1;

    Serial.print( "sat = ");   Serial.print(sat);
    Serial.print( " value ");   Serial.println( value);

    color1 = HSV(hue1, sat, value);
    color2 = HSV(hue2, sat, value);
    color3 = HSV(hue3, sat, value);

     // setTube1(color1);
    //    setTube2(color2);
    //    setTube3(color3);

    color = HSV(hue1, (uint8_t)sat, (uint8_t)value);
    setColors(color);
   
    if (value > 4.0) {
      lastActive = millis();
    }

checkActive();

  }

}




