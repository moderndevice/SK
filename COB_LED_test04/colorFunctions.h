// Simple HSV function
// Doesn't address white channel yet
uint32_t HSV(byte Hue, byte Sat, byte Value ) {
  float white, red, green, blue,  total;
  int lowSatRed, lowSatGreen, lowSatBlue;


  if (Hue < 100) {   // 0 - 100 red to yellows to green
    red = (255 - Hue * 255.0 / 100.0) * (Value / 255.0);
    green =  (Hue * 255.0 / 100.0) * (Value / 255.0);
    blue = 0;
    // compute sat from total red & green vals
    total = red + green + blue;
    //now linear average between all chans equal (no sat) and brightest sat
    lowSatRed = lowSatGreen = lowSatBlue = total / 3;

    red = (Sat * red) / 255  +  ((255 - Sat) * lowSatRed) / 255;
    green = (Sat * green) / 255  +  ((255 - Sat) * lowSatGreen) / 255;
    blue = (Sat * blue) / 255  +  ((255 - Sat) * lowSatBlue) / 255;

    white = ((255.0 - Sat) * Value) / 512.0;

    return ((uint32_t)white << 24) + ((uint32_t)red << 16) + ((uint32_t)green << 8) + (uint32_t)blue;
  }

  if (Hue < 175) {  // 75  green to blue
    Hue -= 100;
    red = 0;
    green =  (255 - Hue * 255.0 / 75.0) * (Value / 255.0);
    blue = (Hue * 255.0 / 75.0) * (Value / 255.0) ;

    total = red + green + blue;
    lowSatRed = lowSatGreen = lowSatBlue = total / 3;

    red = (Sat * red) / 255  +  ((255 - Sat) * lowSatRed) / 255;
    green = (Sat * green) / 255  +  ((255 - Sat) * lowSatGreen) / 255;
    blue = (Sat * blue) / 255  +  ((255 - Sat) * lowSatBlue) / 255;

    white = ((255.0 - Sat) * Value) / 512.0;

    return ((uint32_t)white << 24) + ((uint32_t)red << 16) + ((uint32_t)green << 8) + (uint32_t)blue;
    //return strip.Color(0, 255 - Hue * 3.64285714, Hue * 3.64285714,  0);
  }

  Hue -= 175;     // 80 blue to purple to red
  red = (Hue * 255.0 / 80.0) * (Value / 255.0);
  green = 0;
  blue = (255 - Hue * 255.0 / 80.0) * (Value / 255.0);

  total = red + green + blue;
  lowSatRed = lowSatGreen = lowSatBlue = total / 3;

  red = (Sat * red) / 255  +  ((255 - Sat) * lowSatRed) / 255;
  green = (Sat * green) / 255  +  ((255 - Sat) * lowSatGreen) / 255;
  blue = (Sat * blue) / 255  +  ((255 - Sat) * lowSatBlue) / 255;

  white = ((255.0 - Sat) * Value) / 512.0;
  return ((uint32_t)white << 24) + ((uint32_t)red << 16) + ((uint32_t)green << 8) + (uint32_t)blue;
  //return strip.Color(Hue * 3.4, 0, 255 - Hue * 3.4,  0);
}

void setColors( uint32_t color) {

  // uint8_t white, uint8_t red,  uint8_t green,  uint8_t blue

  uint8_t white = color >> 24;
  uint8_t  red = color >> 16;
  uint8_t  green = color >> 8;
  uint8_t  blue = color;

  for (int i = 0; i < 3; i++) {
    analogWrite(greenPins[i], green);
    analogWrite(redPins[i], red);

    analogWrite(bluePins[i], blue);
    analogWrite(whitePins[i], white);
  }
}

void setTube1(uint32_t color1) {

  uint8_t white = color1 >> 24;
  uint8_t  red = color1 >> 16;
  uint8_t  green = color1 >> 8;
  uint8_t  blue = color1;

  analogWrite(32, white); // w
  analogWrite(9, red); // r
  analogWrite(10, green);  // g
  analogWrite(25, blue);   // b
}

void setTube2(uint32_t color2) {
  analogWrite(5, (uint8_t) (color2 >> 24)); // w
  analogWrite(6, (uint8_t) (color2 >> 16)); // r
  analogWrite(3, (uint8_t) (color2 >> 8));  // g
  analogWrite(4, (uint8_t) color2);   // b
}

void setTube3(uint32_t color3) {
  analogWrite(20, (uint8_t) (color3 >> 24)); // w
  analogWrite(23, (uint8_t) (color3 >> 16)); // r
  analogWrite(22, (uint8_t) (color3 >> 8));  // g
  analogWrite(21, (uint8_t) color3);   // b
}


uint32_t fadeToBlack(uint32_t color, float factor) {
  uint8_t white = (float)(color >> 24) * factor;
  uint8_t  red = (float)(color >> 16) * factor;
  uint8_t  green = (float)(color >> 8) * factor;
  uint8_t  blue = (float)color * factor;

  return ((white << 24) + (red << 16) + (green << 8) + blue);
}



