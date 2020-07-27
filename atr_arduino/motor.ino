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
  if(mapped_pwm_vals[0] == 0 || mapped_pwm_vals[1] == 0 || estop){
    all_stop();
  }
  if(!estop){
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
}
