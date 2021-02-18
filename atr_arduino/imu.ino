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

}

void print_imu(){
  Serial.print("Roll: "+String(roll));
  Serial.print(" Pitch: "+String(pitch));
  Serial.print(" Heading: "+String(heading));
  Serial.print(" Temperature: "+String(temp)+"\n");
}
