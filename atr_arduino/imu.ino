void update_imu(){
    
  if (dof.fusionGetOrientation(&accel_event, &mag_event, &orientation))
  {
    roll = orientation.roll;
    pitch = orientation.pitch;
    heading = orientation.heading;
  }
  
  if (bmp_event.pressure)
  {
    bmp.getTemperature(&temp);
  }

  // Roll moving average calculation
  roll_ma_total = roll_ma_total - roll_ma_readings[roll_ma_readIndex];
  roll_ma_readings[roll_ma_readIndex] = roll;
  roll_ma_total = roll_ma_total + roll_ma_readings[roll_ma_readIndex];
  roll_ma_readIndex +=1;
  if (roll_ma_readIndex >= roll_ma_num_readings) {
    roll_ma_readIndex = 0;
  }
  roll_ma = roll_ma_total / roll_ma_num_readings;
}

void print_imu(){
  Serial.print("Roll: "+String(roll));
  Serial.print(" Pitch: "+String(pitch));
  Serial.print(" Heading: "+String(heading));
  Serial.print(" Temperature: "+String(temp)+"\n");
}
