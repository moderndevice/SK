/*
 COB LED test
 */

int whitePin = 5;    // LED connected to digital pin 9
int redPin = 9;    // LED connected to digital pin 9
int greenPin = 10;    // LED connected to digital pin 9
int bluePin = 11;    // LED connected to digital pin 9

void setup() {
  // nothing happens in setup
}

void loop() {
  for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 5) {
    // sets the value (range from 0 to 255):
    analogWrite(whitePin, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
  }

  for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) {
    // sets the value (range from 0 to 255):
    analogWrite(whitePin, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
  }

    for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 5) {
    // sets the value (range from 0 to 255):
    analogWrite(redPin, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
  }

  for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) {
    // sets the value (range from 0 to 255):
    analogWrite(redPin, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
  }

    for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 5) {
    // sets the value (range from 0 to 255):
    analogWrite(greenPin, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
  }

  for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) {
    // sets the value (range from 0 to 255):
    analogWrite(greenPin, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
  }

    for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 5) {
    // sets the value (range from 0 to 255):
    analogWrite(bluePin, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
  }

  for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) {
    // sets the value (range from 0 to 255):
    analogWrite(bluePin, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
  }
}
