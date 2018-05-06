void  readSensors() {
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
  angle_S = atan2(tilty, tiltx);

  angle = (angle_S + 3.14) * 255.0 / (2 * PI); // map angle to 0-255 for HSV function

  TiltXY = abs(tiltx) + abs(tilty);

#ifdef DEBUG_ACCEL_RAW  // Then print out the raw data
  Serial.print("X:  "); Serial.print(lis.x);
  Serial.print("  \tY:  "); Serial.print(lis.y);
  Serial.print("  \tZ:  "); Serial.print(lis.z);
#endif

#ifdef DEBUG_ACCEL_TILT
  Serial.print(" tiltx  "); Serial.print(tiltx);
  Serial.print("  \ttilty  "); Serial.print(tilty);
  Serial.print("  \ttiltz  "); Serial.print(tiltz);
  Serial.print("  \tangle  "); Serial.print(angle);
  Serial.print("  \ttiltXY  "); Serial.print(TiltXY);
   Serial.print("  \tactiveLevel  "); Serial.println(activeLevel);
#endif

#ifdef DEBUG_ACCEL_CHANGE
  Serial.print(" changeX  ");      Serial.print(changeX);
  Serial.print("  \tchangeY  ");   Serial.print(changeY);
  Serial.print("  \tchangez  "); Serial.println(changeZ);
#endif

if (TiltXY > TILT_THRESH){
	activeLevel += (TiltXY * 4);
}

activeLevel *= FALLOFF_FACTOR;
if (activeLevel < 0.0) activeLevel = 0.0;
if (activeLevel > 255.0) activeLevel = 255.0;

}

