// All Terrain Rover - RC Operation
// Badar Jahangir Kayani
// 2/8/2020

#include "variables.h"
#include "constants.h"

#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>
#include "RoboClaw.h"

SoftwareSerial serial(15,14);  
RoboClaw roboclaw(&serial,10000);
Adafruit_NeoPixel front_strip(led_count, led_strip_front, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel back_strip(led_count, led_strip_back, NEO_GRB + NEO_KHZ800);

unsigned long dur;

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

  colorWipe(back_strip.Color(0,   50,   255), 0, 2);  
  Serial.begin(9600);
}

void loop() {
  update_rc_input();
  update_motor_speed();
}

void right_forward(int val){
  roboclaw.BackwardM2(add_1,val);
  roboclaw.ForwardM1(add_2,val);
}

void right_backward(int val){
  roboclaw.ForwardM2(add_1,val);
  roboclaw.BackwardM1(add_2,val);
}

void left_forward(int val){
  roboclaw.BackwardM1(add_1,val);
  roboclaw.ForwardM2(add_2,val);
}

void left_backward(int val){
  roboclaw.ForwardM1(add_1,val);
  roboclaw.BackwardM2(add_2,val);
}

void all_stop(){
  roboclaw.ForwardM1(add_1,0);
  roboclaw.ForwardM1(add_2,0);
  roboclaw.ForwardM2(add_1,0);
  roboclaw.ForwardM2(add_2,0);
}

void update_rc_input(){
  rc_vals[0] = pulseIn(rc_ch_1, HIGH, pulse_timeout);
  rc_vals[1] = pulseIn(rc_ch_2, HIGH, pulse_timeout);
  rc_vals[2] = pulseIn(rc_ch_3, HIGH, pulse_timeout);
  rc_vals[3] = pulseIn(rc_ch_4, HIGH, pulse_timeout);
  if(rc_vals[1] == 0 && rc_vals[2] == 0){
    mapped_pwm_vals[0] = 0;
    mapped_pwm_vals[1] = 0;
  }
  else{
    mapped_pwm_vals[0] = map(rc_vals[1], rc_lower_limit,
                             rc_upper_limit, rc_mapped_lower_limit, 
                             rc_mapped_upper_limit);
    mapped_pwm_vals[1] = map(rc_vals[2], rc_lower_limit,
                             rc_upper_limit, rc_mapped_lower_limit, 
                             rc_mapped_upper_limit);
  }
  
  if(abs(mapped_pwm_vals[0])<=rc_mapped_dead_band){
    mapped_pwm_vals[0] = 0;
  }
  else if(abs(mapped_pwm_vals[0])>=rc_mapped_upper_limit){
    mapped_pwm_vals[0] = sign(mapped_pwm_vals[0])*rc_mapped_upper_limit;
  }
  if(abs(mapped_pwm_vals[1])<=rc_mapped_dead_band){
    mapped_pwm_vals[1] = 0;
  }
  else if(abs(mapped_pwm_vals[1])>=rc_mapped_upper_limit){
    mapped_pwm_vals[1] = sign(mapped_pwm_vals[1])*rc_mapped_upper_limit;
  }
}

void print_rc_vals(){
    Serial.print("RC Input: ");
    Serial.print(String(rc_vals[0])+' ');
    Serial.print(String(rc_vals[1])+' ');
    Serial.print(String(rc_vals[2])+' ');
    Serial.print(String(rc_vals[3])+'\n');
}

void print_mapped_vals(){
  Serial.print("Mapped Input: ");
  Serial.print(String(mapped_pwm_vals[0])+' ');
  Serial.print(String(mapped_pwm_vals[1])+'\n');
}

int sign(int val){
  int sign;
  if(val > 0)
    sign = 1;
  else if(val < 0)
    sign = -1;
  else
    sign = 0;
  return sign;
}

void update_motor_speed(){
  if(mapped_pwm_vals[0] == 0 || mapped_pwm_vals[1] == 0){
    all_stop();
  }
  //left stick forward
  if(mapped_pwm_vals[0] > 0){
    left_forward(abs(mapped_pwm_vals[0]));
  }
  //left stick backward
  else if(mapped_pwm_vals[0] < 0){
    left_backward(abs(mapped_pwm_vals[0]));
  }
  //right stick forward
  if(mapped_pwm_vals[1] > 0){
    right_forward(abs(mapped_pwm_vals[1]));
  }
  //right stick backward
  else if(mapped_pwm_vals[1] < 0){
    right_backward(abs(mapped_pwm_vals[1]));
  }
  
}

void colorWipe(uint32_t color, int wait, int strip) {
  if(strip == 0){
    for(int i=0; i<led_count; i++) { 
    front_strip.setPixelColor(i, color);
    front_strip.show();     
    delay(wait);                    
  }}
  else if(strip == 1){
    for(int i=0; i<led_count; i++) { 
    back_strip.setPixelColor(i, color);
    back_strip.show();     
    delay(wait);
  }}
  else if(strip == 2){
    for(int i=0; i<led_count; i++) { 
    front_strip.setPixelColor(i, color);
    back_strip.setPixelColor(i, color);
    front_strip.show();     
    back_strip.show();
    delay(wait);
  }}
  else{
    front_strip.clear();
    back_strip.clear();
    front_strip.show();
    back_strip.show();
  }
}
