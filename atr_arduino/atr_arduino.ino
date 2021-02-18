// All Terrain Rover - RC Operation
// Badar Jahangir Kayani

// GPS not working due to timing issues

#include "variables.h"
#include "constants.h"

#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>
#include "RoboClaw.h"

#include <thermistor.h>

thermistor motor_a_therm(temp_sens_a,0);
thermistor motor_b_therm(temp_sens_b,0);
thermistor motor_c_therm(temp_sens_c,0);
thermistor motor_d_therm(temp_sens_d,0);

RoboClaw roboclaw(&RoboClawSerial,10000);
Adafruit_NeoPixel front_strip(led_count, led_strip_front, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel back_strip(led_count, led_strip_back, NEO_GRB + NEO_KHZ800);

#include <Adafruit_GPS.h>
Adafruit_GPS GPS(&GPSSerial);

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_BMP085_U.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_10DOF.h>

Adafruit_10DOF                dof   = Adafruit_10DOF();
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(30301);
Adafruit_LSM303_Mag_Unified   mag   = Adafruit_LSM303_Mag_Unified(30302);
Adafruit_BMP085_Unified       bmp   = Adafruit_BMP085_Unified(18001);

sensors_event_t accel_event;
sensors_event_t mag_event;
sensors_event_t bmp_event;
sensors_vec_t   orientation;

void setup() {
  roboclaw.begin(baudrate);
  pinMode(rc_ch_1, INPUT);
  pinMode(rc_ch_2, INPUT);
  pinMode(rc_ch_3, INPUT);
  pinMode(rc_ch_4, INPUT);

  front_strip.begin();
  back_strip.begin();
  front_strip.show();
  back_strip.show();
  front_strip.setBrightness(255);
  back_strip.setBrightness(255);

  colorWipe(back_strip.Color(0,   50,   255), 2);  
  Serial.begin(115200);

  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);

  accel.begin();
  mag.begin();
  bmp.begin();

  delay(1000);
}

void loop() {
  accel.getEvent(&accel_event);
  mag.getEvent(&mag_event);
  bmp.getEvent(&bmp_event);
  
  current_time = millis();
  GPS.read();

  if (GPS.newNMEAreceived()) {
    GPS.lastNMEA(); 
    if (!GPS.parse(GPS.lastNMEA()))
      return; 
  }

  if((current_time - last_control_loop) >= CONTROL_LOOP_RATE){
    update_rc_input();
    update_imu();
    update_motor_speed();
    last_control_loop = millis();
  }

  if((current_time - last_sensor_update) >= SENSOR_UPDATE_RATE){
    update_motor_temps();
    update_gps();
    voltage_update();
    current_update();
    last_sensor_update = millis();
  }

  if((current_time - last_debug) >= DEBUG_RATE){
    //print_motor_temps();
    //print_mapped_vals();
    //print_rc_vals();
    //print_gps();
    //print_power_stats();
    //print_imu();
    last_debug = millis();
  }
}
