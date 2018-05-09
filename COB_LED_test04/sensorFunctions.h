


void  readAnalogAccel1() {
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
  angle1 = atan2(tilty1, tiltx1);
  tiltXY1 = abs(tilty1) + abs(tiltx1);

#ifdef DEBUG_ACCEL_TILT1
  //  Serial.print(" tiltx1  "); Serial.print(tiltx1);
  //  Serial.print("  \ttilty1  "); Serial.print(tilty1);
  //  Serial.print("  \ttiltz1  "); Serial.print(tiltz1);
  Serial.print("  \tangle1  "); Serial.print(angle1);
  Serial.print("  \ttiltXY1  "); Serial.print(tiltXY1);
#endif

}


void readAccel2() {

  lis2.read();      // get X Y and Z data at once

  accelX2 = lis2.x ;
  accelY2 = lis2.y ;
  accelZ2 = lis2.z ;

  changeX2 = abs(lastX2 - accelX2);
  changeY2 = abs(lastY2 - accelY2);
  changeZ2 = abs(lastZ2 - accelZ2);

  changeT2 = changeX2 + changeY2;

  lastX2 = accelX2;
  lastY2 = accelY2;
  lastZ2 = accelZ2;

  tiltx2 = atan2((float)accelX2, sqrt(((float)accelY2 * (float)accelY2) + ((float)accelZ2 * (float)accelZ2)));
  tilty2 = atan2((float)accelY2, sqrt(((float)accelX2 * (float)accelX2) + ((float)accelZ2 * (float)accelZ2)));
  tiltz2 = atan2((float)accelZ2, sqrt(((float)accelY2 * (float)accelY2) + ((float)accelX2 * (float)accelX2)));
  angle2 = atan2(tilty2, tiltx2);
  tiltXY2 = abs(tilty2) + abs(tiltx2);

#ifdef define DEBUG_ACCEL_RAW2  // Then print out the raw data
  Serial.print("         X:  "); Serial.print(lis2.x);
  Serial.print("  \tY:  "); Serial.print(lis2.y);
  Serial.print("  \tZ:  "); Serial.print(lis2.z);
#endif

#ifdef DEBUG_ACCEL_TILT2
  //  Serial.print(" tiltx2  "); Serial.print(tiltx2);
  //  Serial.print("  \ttilty2  "); Serial.print(tilty2);
  //  Serial.print("  \ttiltz2  "); Serial.print(tiltz2);
   Serial.print("  \t changeT2  "); Serial.print(changeT2);
  Serial.print("  \t angle2  "); Serial.print(angle2);
  Serial.print("  \t tiltXY2  "); Serial.print(tiltXY2);
#endif

#ifdef DEBUG_ACCEL_CHANGE
  Serial.print(" changeX  ");      Serial.print(changeX);
  Serial.print("  \tchangeY  ");   Serial.print(changeY);
  Serial.print("  \tchangez  "); Serial.print(changeZ);
#endif

}

void readAccel3() {

  lis3.read();      // get X Y and Z data at once

  accelX3 = lis3.x ;
  accelY3 = lis3.y ;
  accelZ3 = lis3.z ;

  changeX3 = abs(lastX3 - accelX3);
  changeY3 = abs(lastY3 - accelY3);
  changeZ3 = abs(lastZ3 - accelZ3);

  lastX3 = accelX3;
  lastY3 = accelY3;
  lastZ3 = accelZ3;

  tiltx3 = atan2((float)accelX3, sqrt(((float)accelY3 * (float)accelY3) + ((float)accelZ3 * (float)accelZ3)));
  tilty3 = atan2((float)accelY3, sqrt(((float)accelX3 * (float)accelX3) + ((float)accelZ3 * (float)accelZ3)));
  tiltz3 = atan2((float)accelZ3, sqrt(((float)accelY3 * (float)accelY3) + ((float)accelX3 * (float)accelX3)));
  angle3 = atan2(tilty3, tiltx3);
  tiltXY3 = abs(tilty3) + abs(tiltx3);

#ifdef define DEBUG_ACCEL_RAW3  // Then print out the raw data
  Serial.print("X:  "); Serial.print(lis3.x);
  Serial.print("  \tY:  "); Serial.print(lis3.y);
  Serial.print("  \tZ:  "); Serial.print(lis3.z);
#endif

#ifdef DEBUG_ACCEL_TILT3
  //  Serial.print(" \t tiltx3  "); Serial.print(tiltx3);
  //  Serial.print("  \t tilty3  "); Serial.print(tilty3);
  //  Serial.print("  \ttiltz3  "); Serial.print(tiltz3);
  Serial.print("  \tangle3  "); Serial.print(angle3);
  Serial.print("  \t tiltXY3  "); Serial.println(tiltXY3);
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

int compareAccel() {
  if ( (tiltXY1 > TILT_THRESH) || (tiltXY2 > TILT_THRESH) || (tiltXY3 > TILT_THRESH)) {
    Serial.println("past thresh");
    if ( tiltXY1 > tiltXY2) {
    if ( tiltXY1 > tiltXY3) {
        maxAccelNo = 1;
        return maxAccelNo;
      }
      else maxAccelNo = 3;
      return maxAccelNo;
    }
    else {   // 2 larger

      if ( tiltXY2 > tiltXY3) {
        maxAccelNo = 2;
        return maxAccelNo;
      }
      else maxAccelNo = 3;
      return maxAccelNo;
    }
  }
  else {
    return 0;
  }
}


