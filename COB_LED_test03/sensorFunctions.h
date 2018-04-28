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


int smooth(int data, float filterVal, float smoothedVal){


  if (filterVal > 1){      // check to make sure param's are within range
    filterVal = .99;
  }
  else if (filterVal <= 0){
    filterVal = 0;
  }

  smoothedVal = (data * (1 - filterVal)) + (smoothedVal  *  filterVal);

  return (int)smoothedVal;
}

