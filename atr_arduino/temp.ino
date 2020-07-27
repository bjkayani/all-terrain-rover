
void update_motor_temps(){
  motor_temps[0] = motor_a_therm.analog2temp();
  motor_temps[1] = motor_b_therm.analog2temp();
  motor_temps[2] = motor_c_therm.analog2temp();
  motor_temps[3] = motor_d_therm.analog2temp();
}

void print_motor_temps(){
  Serial.print("");
  Serial.print(String(motor_temps[0])+' ');
  Serial.print(String(motor_temps[1])+' ');
  Serial.print(String(motor_temps[2])+' ');
  Serial.print(String(motor_temps[3])+'\n');
}
