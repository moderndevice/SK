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

    white = ((255.0 - Sat) * Value) / 255.0;

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

    white = ((255.0 - Sat) * Value) / 255.0;

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

  white = ((255.0 - Sat) * Value) / 255.0;
  return ((uint32_t)white << 24) + ((uint32_t)red << 16) + ((uint32_t)green << 8) + (uint32_t)blue;
  //return strip.Color(Hue * 3.4, 0, 255 - Hue * 3.4,  0);


}


