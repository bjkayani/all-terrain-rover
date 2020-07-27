void update_gps(){
    gps_fix = GPS.fix;
    gps_quality = GPS.fixquality;
    second = GPS.seconds;
    minute = GPS.minute;
    hour = GPS.hour;
    day = GPS.day;
    month = GPS.month;
    year = GPS.year;
  
    if(gps_fix){
      latitude = GPS.latitude;
      longitude = GPS.longitude;
      gps_speed = GPS.speed;
      angle = GPS.angle;
      altitude = GPS.altitude;
      satellites = GPS.satellites;
    }
}

void print_gps(){
    Serial.print("Time: "+String(hour));
    Serial.print(":"+String(minute)+":");
    Serial.print(String(second)+" Date: ");
    Serial.print(String(month)+"/"+String(day));
    Serial.print("/"+String(year)+" ");
  
    if(gps_fix){
      Serial.print("Location: "+String(latitude));
      Serial.print(" "+String(longitude)+" Speed: ");
      Serial.print(String(gps_speed)+" Altitude: ");
      Serial.print(String(altitude)+" Angle: "+String(angle));  
      Serial.print(" Satellites: "+String(satellites)+"\n");
    }
    else{
      Serial.print("No GPS Fix\n");
    }
}
