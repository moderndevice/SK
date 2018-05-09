/* SKxx
    Drives WS2811 LED strands
    Uses an accelermeter for a sensor

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

#define DATA_PIN    8
#define LED_TYPE     WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    190
CRGB leds[NUM_LEDS];

#define BRIGHTNESS         255
#define FRAMES_PER_SECOND  120

Adafruit_LIS3DH lis = Adafruit_LIS3DH();

// #define DEBUG_ACCEL_RAW
#define DEBUG_ACCEL_TILT
//#define DEBUG_ACCEL_CHANGE
#define DEBUG_COLOR
#define TILT_THRESH 0.1
#define FALLOFF_FACTOR 0.999;  // must be close to 1 but less than 1 eg 0.999

int32_t accelX, accelY, accelZ, lastX, lastY, lastZ, changeX, changeY, changeZ, angle;  // accel globals
float  tiltx, tilty, tiltz, angle_S, TiltXY;
float activeLevel = 0;

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
  // juggleOriginal();
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

void juggleOriginal() {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds, NUM_LEDS, 20);
  static byte dothue = 0;
  for ( int i = 0; i < 8; i++) {
    // beatsin16 	( 	accum88  	beats_per_minute,
    // uint16_t  	lowest = 0, uint16_t  	highest = 65535, uint32_t  	timebase = 0, uint16_t phase_offset = 0 )
    leds[beatsin16(50, 10, NUM_LEDS)] |= CHSV(dothue, 120 + random(200), 255);
    dothue += 8;
  }
}

void juggle() {

  static uint8_t color;
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds, NUM_LEDS, 30);
  byte dothue = 0;
  for ( int i = 0; i < ((uint8_t)activeLevel / 16); i++) {

    if (TiltXY > 0.1) {
      color = (uint8_t)angle;
      //	beatsin16 (accum88 beats_per_minute, uint16_t lowest=0, uint16_t highest=65535, uint32_t timebase=0, uint16_t phase_offset=0)
      leds[beatsin16(i + (uint8_t)activeLevel, 20, NUM_LEDS)] |= CHSV( color, random(128) + 128, activeLevel);
      dothue += 16;
    }
    else {
      color = dothue;
      //	beatsin16 (accum88 beats_per_minute, uint16_t lowest=0, uint16_t highest=65535, uint32_t timebase=0, uint16_t phase_offset=0)
      leds[beatsin16(i + (uint8_t)activeLevel, 20, NUM_LEDS)] |= CHSV( color, random(50) + 20, activeLevel);
      dothue += 16;
    }

  }
}

