/*
  COB_LED code
  Drive COB LEDs using an accelerometer
  Uses some code derived from Adafruit NeoPixel library
*/

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>
#include "colorFunctions.h"


Adafruit_LIS3DH lis = Adafruit_LIS3DH();

const int whitePin = 11;   // LED connected to digital pin 9
const int bluePin = 10;    // LED connected to digital pin 9
const int greenPin = 9;    // LED connected to digital pin 9
const int redPin = 5;      // LED connected to digital pin 9


float accelX1, accelY1, accelZ1, lastX1, lastY1, lastZ1;
float  tiltx1, tilty1, tiltz1, angle1;

int accelX, accelY, accelZ, lastX, lastY, lastZ, changeX, changeY, changeZ;
float  tiltx, tilty, tiltz, angle;

uint8_t white, red, green, blue;

/******  DEBUGGING / PRINTING ******/
#define DEBUG_ACCEL_RAW1 // analog accel
// #define DEBUG_ACCEL_RAW
#define DEBUG_ACCEL_TILT1
// #define DEBUG_ACCEL_TILT
//#define DEBUG_ACCEL_CHANGE
#define DEBUG_COLOR


#include "sensorFunctions.h"

void setup() {
  // nothing happens in setup
  pinMode(whitePin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  Serial.begin(57600);
  Serial.println("LIS3DH test!");

  if (! lis.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
   // while (1);
  }
  Serial.println("LIS3DH found!");
  lis.setRange(LIS3DH_RANGE_4_G);   // 2, 4, 8 or 16 G!

}

void loop() {
  static int changeRaw, change;
  int sat;
  int angle2;
  uint32_t color;
  int angleT;

readAccel1();
  //readAccel();
return;

  angle2 = (angle + 3.14) * 255.0 / (2 * PI); // map angle to 0-255 for HSV function

  changeRaw = ((changeX + changeY) / 3.0) - 100;
  changeRaw = constrain(changeRaw, 0, 255);
  Serial.print("  changeRaw  "); Serial.println(changeRaw);
  //delay(500);

  if (changeRaw ) {
    angle2 = (angle + 3.14) * 255.0 / (2 * PI); // map angle to 0-255 for HSV function

    sat = constrain (((abs(tiltx) * 6 + abs(tilty) * 4) * 255), 0, 255);
    color = HSV(angle2, sat, 255);
    white = color >> 24;
    red = color >> 16;
    green = color >> 8;
    blue = color;
    int j = changeRaw;
    for (float i = changeRaw; i > 0.1; i *= 0.995) {
      //  readAccel();
      changeRaw = ((changeX + changeY) / 3.0) - 100;
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

      analogWrite(whitePin, white);
      analogWrite(redPin, red) ;
      analogWrite(greenPin, green );
      analogWrite(bluePin, blue);


#ifdef DEBUG_COLOR

      //      Serial.print(" white  "); Serial.print(white);
      //      Serial.print(" red  "); Serial.print(redT);
      //      Serial.print("  green  "); Serial.print(greenT);
      //      Serial.print("  blue  "); Serial.println(blueT);

#endif
      delay(1);

    }
    color = HSV(angle , 255, 255);

    white = color >> 24;
    red = color >> 16;
    green = color >> 8;
    blue = color;


    analogWrite(whitePin, white);
    analogWrite(redPin, red) ;
    analogWrite(greenPin, green );
    analogWrite(bluePin, blue);

    delay(20);

    analogWrite(whitePin, 0);
    analogWrite(redPin, 0) ;
    analogWrite(greenPin, 0 );
    analogWrite(bluePin, 0);


  }

  change =  smooth(changeRaw, 0.8, change);


  sat = constrain (((abs(tiltx) * 2 + abs(tilty) * 2) * 255), 0, 255);
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

