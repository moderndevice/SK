


void  readAccel1() {
   accelX1 = analogRead(16);      // read analog pin for x raw
   accelY1 = analogRead(15);      // read analog pin for y raw
   accelZ1 = analogRead(14);      // read analog pin for z raw

#ifdef DEBUG_ACCEL_RAW1  // prints only if defined above
  Serial.print(" xr ");
  Serial.print(accelX1);  // 238   718
  Serial.print("\t");
  Serial.print(" yr ");
  Serial.print(accelY1);  // 290    776
  Serial.print("\t");
  Serial.print(" zr ");
  Serial.print(accelZ1);  // 190   670
  Serial.println("\t");
#endif

  //  x = (accelX1 - xMid) / (float)xRng;  //shift range down by midpoint for signed result
  accelX1 = (accelX1 - 478.0) / 480.0;  //shift range down by midpoint for signed result
  //  y = (accelY1 - yMid) / (float)yRng;
  accelY1 = (accelY1 - 533.0) / 486.0;
  //  z = (accelZ1 - zMid) / (float)zRng;
  accelZ1   = (accelZ1 - 430.0) / 480.0;
  //

#ifdef DEBUG_ACCEL_RAW1  // prints only if defined above
  Serial.print(" xr ");
  Serial.print(accelX1);  //238  718
  Serial.print("\t");
  Serial.print(" yr ");
  Serial.print(accelY1);  //290  776
  Serial.print("\t");
  Serial.print(" zr ");
  Serial.print(accelZ1);  //190        670
  Serial.println("\t");
#endif


    // you might want to comment out tilt calculations below that you are not using as these
    // floating point trig calculations are fairly slow.
    tiltx1 = atan2((float)accelX1, sqrt(((float)accelY1 * (float)accelY1) + ((float)accelZ1 * (float)accelZ1)));
    tilty1 = atan2((float)accelY1, sqrt(((float)accelX1 * (float)accelX1) + ((float)accelZ1 * (float)accelZ1)));
    tiltz1 = atan2((float)accelZ1, sqrt(((float)accelY1 * (float)accelY1) + ((float)accelX1 * (float)accelX1)));
    angle1 = atan2(tilty, tiltx);
  
  #ifdef DEBUG_ACCEL_TILT1
    Serial.print(" tiltx  "); Serial.print(tiltx);
    Serial.print("  \ttilty  "); Serial.print(tilty);
    Serial.print("  \ttiltz  "); Serial.print(tiltz);
    Serial.print("  \tangle  "); Serial.println(angle);
  #endif

}






void readAccel() {

  lastX = accelX;
  lastY = accelY;
  lastZ = accelZ;

  lis.read();      // get X Y and Z data at once

  accelX = lis.x ;
  accelY = lis.y ;
  accelZ = lis.z ;

  changeX = abs(lastX - accelX);
  changeY = abs(lastY - accelY);
  changeZ = abs(lastZ - accelZ);

  tiltx = atan2((float)accelX, sqrt(((float)accelY * (float)accelY) + ((float)accelZ * (float)accelZ)));
  tilty = atan2((float)accelY, sqrt(((float)accelX * (float)accelX) + ((float)accelZ * (float)accelZ)));
  tiltz = atan2((float)accelZ, sqrt(((float)accelY * (float)accelY) + ((float)accelX * (float)accelX)));
  angle = atan2(tilty, tiltx);

#ifdef DEBUG_ACCEL_RAW  // Then print out the raw data
  Serial.print("X:  "); Serial.print(lis.x);
  Serial.print("  \tY:  "); Serial.print(lis.y);
  Serial.print("  \tZ:  "); Serial.print(lis.z);
#endif

#ifdef DEBUG_ACCEL_TILT
  Serial.print(" tiltx  "); Serial.print(tiltx);
  Serial.print("  \ttilty  "); Serial.print(tilty);
  Serial.print("  \ttiltz  "); Serial.print(tiltz);
  Serial.print("  \tangle  "); Serial.println(angle);
#endif

#ifdef DEBUG_ACCEL_CHANGE
  Serial.print(" changeX  ");      Serial.print(changeX);
  Serial.print("  \tchangeY  ");   Serial.print(changeY);
  Serial.print("  \tchangez  "); Serial.println(changeZ);
#endif

}


int smooth(int data, float filterVal, float smoothedVal) {


  if (filterVal > 1) {     // check to make sure param's are within range
    filterVal = .99;
  }
  else if (filterVal <= 0) {
    filterVal = 0;
  }

  smoothedVal = (data * (1 - filterVal)) + (smoothedVal  *  filterVal);

  return (int)smoothedVal;
}

