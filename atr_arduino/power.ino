void current_update(){
  int16_t a, b;
  if(roboclaw.ReadCurrents(add_1, a, b)){
    motor_currents[0] = a;
    motor_currents[1] = b;
  }
  if(roboclaw.ReadCurrents(add_2, a, b)){
    motor_currents[2] = a;
    motor_currents[3] = b;
  }
}

void voltage_update(){
  int16_t volt_1 = roboclaw.ReadMainBatteryVoltage(add_1);
  batt_voltage = (float)volt_1 / 10;
}

void print_power_stats(){
  Serial.print("Battery Voltage: " + String(batt_voltage));
  Serial.print(" Motor Current: A:" + String(motor_currents[0]));
  Serial.print(" B:" + String(motor_currents[1]));
  Serial.print(" C:" + String(motor_currents[2]));
  Serial.print(" D:" + String(motor_currents[3]) + "\n");
}
