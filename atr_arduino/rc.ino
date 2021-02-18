//need to speed this up

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

  if(rc_vals[0] < 1200){
    estop = true;
  }
  else if(rc_vals[0] > 1600){
    estop = false;
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
