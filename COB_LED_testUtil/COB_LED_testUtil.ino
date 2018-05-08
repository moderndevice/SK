/*
  COB LED test
*/

int whitePin = 5;    // LED connected to digital pin 9
int redPin = 9;    // LED connected to digital pin 9
int greenPin = 10;    // LED connected to digital pin 9
int bluePin = 11;    // LED connected to digital pin 9

int pins[] = { 3, 4, 5, 6,     9, 10, 25, 32,     20, 21, 22, 23};

void setup() {
  for (int i = 0; i < 12; i++) {
    analogWrite(pins[i], 0);
  }
}

void loop() {
  for (int i = 0; i < 12; i++) {
    fadeLED(pins[i]);
  }
}

void fadeLED(int pin) {
  for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 1) {
    analogWrite(pin, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(2);
  }

  for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 1) {
    analogWrite(pin, fadeValue);
    delay(5);
  }
}


