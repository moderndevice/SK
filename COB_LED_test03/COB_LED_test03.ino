/*
  COB_LED code
  Drive COB LEDs using an accelerometer
  Uses some code derived from Adafruit NeoPixel library
*/

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>



Adafruit_LIS3DH lis2 = Adafruit_LIS3DH();
Adafruit_LIS3DH lis3 = Adafruit_LIS3DH();

int pwmPins[] = { 9, 10, 25, 32,     3, 4, 5, 6,    20, 21, 22, 23};
int redPins[] = {9, 6, 23 };
int greenPins[] = { 10, 3, 22};
int bluePins[] = { 25, 4, 21};
int whitePins[] = { 32, 5, 20 };



float accelX1, accelY1, accelZ1, lastX1, lastY1, lastZ1;
float  tiltx1, tilty1, tiltz1, angle1, tiltXY1;

int accelX2, accelY2, accelZ2, lastX2, lastY2, lastZ2, changeX2, changeY2, changeZ2;
float  tiltx2, tilty2, tiltz2, angle2, tiltXY2;

int accelX3, accelY3, accelZ3, lastX3, lastY3, lastZ3, changeX3, changeY3, changeZ3;
float  tiltx3, tilty3, tiltz3, angle3, tiltXY3;

uint8_t white, red, green, blue;

/******  DEBUGGING / PRINTING ******/
// #define DEBUG_ACCEL_RAW1 // analog accel
#define DEBUG_ACCEL_RAW2
// #define DEBUG_ACCEL_RAW3

#define DEBUG_ACCEL_TILT1
#define DEBUG_ACCEL_TILT2
#define DEBUG_ACCEL_TILT3

//#define DEBUG_ACCEL_CHANGE
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

}

void loop() {
  static int changeRaw, change;
  int sat;
  int angle2;
  uint32_t color;
  int angleT;

  //  readAnalogAccel1();
  //  readAccel2();
  //  readAccel3();

// color pin test
  //int pwmPins[] = { 3, 4, 5, 6,     9, 10, 25, 32,     20, 21, 22, 23};
//  for (int i = 0; i < 12; i++) {
//    Serial.print(" pin "); Serial.println(pwmPins[i]);
//  analogWrite(pwmPins[i], 255);
//    delay(5000);
//    analogWrite(pwmPins[i], 0);
//  } 



//setColors(255, 0, 0, 128);
//delay(5000);
//
//setColors(0, 200, 100, 0);
//delay(5000);
//
//setColors(255, 0, 255, 0);
//delay(5000);

setColors(0, 255, 0, 0);
delay(5000);

return;


  angle2 = (angle2 + 3.14) * 255.0 / (2 * PI); // map angle to 0-255 for HSV function

  changeRaw = ((changeX2 + changeY2) / 3.0) - 100;
  changeRaw = constrain(changeRaw, 0, 255);
  Serial.print("  changeRaw  "); Serial.println(changeRaw);
  //delay(500);

  if (changeRaw ) {
    angle2 = (angle2 + 3.14) * 255.0 / (2 * PI); // map angle to 0-255 for HSV function

    sat = constrain (((abs(tiltx2) * 6 + abs(tilty2) * 4) * 255), 0, 255);
    color = HSV(angle2, sat, 255);
    white = color >> 24;
    red = color >> 16;
    green = color >> 8;
    blue = color;
    int j = changeRaw;
    for (float i = changeRaw; i > 0.1; i *= 0.995) {
      //  readAccel();
      changeRaw = ((changeX2 + changeY2) / 3.0) - 100;
      //  if (changeRaw > 220) return;
      angleT = (int)(angle2 + (i / 3.0)) % 255;
      color = HSV(angleT , sat, (255 * i) / changeRaw);

      white = color >> 24;
      red = color >> 16;
      green = color >> 8;
      blue = color;


      //      int   whiteT = (((float)white * i) / (float)j);
      //      int     redT = (((float)red * i) / (float)j);
      //      int     greenT = (((float)green * i) / (float)j);
      //      int    blueT = (((float)blue * i) / (float)j);

//      analogWrite(whitePin, white);
//      analogWrite(redPin, red) ;
//      analogWrite(greenPin, green );
//      analogWrite(bluePin, blue);


#ifdef DEBUG_COLOR

      //      Serial.print(" white  "); Serial.print(white);
      //      Serial.print(" red  "); Serial.print(redT);
      //      Serial.print("  green  "); Serial.print(greenT);
      //      Serial.print("  blue  "); Serial.println(blueT);

#endif
      delay(1);

    }
    color = HSV(angle2 , 255, 255);

    white = color >> 24;
    red = color >> 16;
    green = color >> 8;
    blue = color;


//    analogWrite(whitePin, white);
//    analogWrite(redPin, red) ;
//    analogWrite(greenPin, green );
//    analogWrite(bluePin, blue);
//
//    delay(20);
//
//    analogWrite(whitePin, 0);
//    analogWrite(redPin, 0) ;
//    analogWrite(greenPin, 0 );
//    analogWrite(bluePin, 0);


  }

  change =  smooth(changeRaw, 0.8, change);


  sat = constrain (((abs(tiltx2) * 2 + abs(tilty2) * 2) * 255), 0, 255);
  color = HSV(angle2, sat, change);
  white = color >> 24;
  red = color >> 16;
  green = color >> 8;
  blue = color;

  //
  //  analogWrite(whitePin, white);
  //  analogWrite(redPin, red);
  //  analogWrite(greenPin, green);
  //  analogWrite(bluePin, blue);

#ifdef DEBUG_COLOR
  Serial.print("  changeRaw  "); Serial.print(changeRaw);
  Serial.print("  angle  "); Serial.print(angle);
  Serial.print("  tangle2  "); Serial.print(angle2);
  Serial.print("  sat  "); Serial.print(sat);
  Serial.print(" white  "); Serial.print(white);
  Serial.print(" red  "); Serial.print(red);
  Serial.print("  green  "); Serial.print(green);
  Serial.print("  blue  "); Serial.println(blue);

#endif



}

