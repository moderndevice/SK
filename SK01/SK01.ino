/* SKxx
 *  Drives WS2811 LED strands 
 *  Uses an accelermeter for a sensor
 *  
 */


#include "FastLED.h"

FASTLED_USING_NAMESPACE

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>


// FastLED "100-lines-of-code" demo reel, showing just a few
// of the kinds of animation patterns you can quickly and easily
// compose using FastLED.
//
// This example also shows one easy way to define multiple
// animations patterns and have them automatically rotate.
//
// -Mark Kriegsman, December 2014

#if FASTLED_VERSION < 3001000
#error "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define DATA_PIN    5
#define LED_TYPE     WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    180
CRGB leds[NUM_LEDS];

#define BRIGHTNESS         255
#define FRAMES_PER_SECOND  120

Adafruit_LIS3DH lis = Adafruit_LIS3DH();

// #define DEBUG_ACCEL_RAW
#define DEBUG_ACCEL_TILT
//#define DEBUG_ACCEL_CHANGE
#define DEBUG_COLOR

int32_t accelX, accelY, accelZ, lastX, lastY, lastZ, changeX, changeY, changeZ, angle;  // accel globals
float  tiltx, tilty, tiltz, angle_S, TiltXY;
int32_t activeLevel = 0;

#include "sensors.h"

void setup() {
  delay(3000); // 3 second delay for recovery

  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  //FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);

  /************ init accel **********/
  Serial.println("LIS3DH test!");
  if (! lis.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1);
  }
  else {
    Serial.println("LIS3DH found!");
    delay(500);
    lis.setRange(LIS3DH_RANGE_4_G);   // 2, 4, 8 or 16 G!
    Serial.print("Range = "); Serial.print(2 << lis.getRange());
    Serial.println("G");
  }
}



// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = { juggle, bpm };

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns

void loop()
{
  readSensors();
  juggle();
  FastLED.show();
  // insert a delay to keep the framerate modest
  FastLED.delay(2);

  // do some periodic updates
  EVERY_N_MILLISECONDS( 20 ) {
    gHue++;  // slowly cycle the "base color" through the rainbow
  }
  // EVERY_N_SECONDS( 10 ) { nextPattern(); } // change patterns periodically
}

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);
}



void addGlitter( fract8 chanceOfGlitter)
{
  if ( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CRGB::White;
  }
}

void confetti()
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( gHue + random8(64), 200, 255);
}

void sinelon()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 20);
  int pos = beatsin16(13, 0, NUM_LEDS);
  leds[pos] += CHSV( gHue, 255, 192);
}

void bpm()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for ( int i = 0; i < NUM_LEDS; i++) { //9948
    leds[i] = ColorFromPalette(palette, gHue + (i * 2), beat - gHue + (i * 10));
  }
}

void juggle() {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds, NUM_LEDS, 30);
  byte dothue = 0;
  for ( int i = 0; i < 6; i++) {
    leds[beatsin16(i + 30, 0, NUM_LEDS)] |= CHSV(dothue, random(200) + 50, 255);
    dothue += 32;
  }
}

