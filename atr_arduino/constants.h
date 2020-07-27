// Roboclaw
#define add_1 0x80
#define add_2 0x81
#define baudrate 38400

// RC Control Pins
#define rc_ch_1 7 // left horizontal - rudder - ch4
#define rc_ch_2 6 // left vertical - throttle - ch3
#define rc_ch_3 5 // right vertical - elevator - ch2
#define rc_ch_4 4 // right horizontal - aileron - ch1
#define rc_ch_5 22
#define rc_ch_6 24
#define rc_ch_7 26
#define rc_ch_8 28

// RC Control Constants
#define rc_upper_limit 1910
#define rc_lower_limit 1060
#define rc_mapped_dead_band 12
#define rc_mapped_lower_limit -127
#define rc_mapped_upper_limit 127
#define pulse_timeout 50000

// LED Strip
#define led_strip_front 8
#define led_strip_back 9
#define led_count 7

// Temperature Sensor Pins
#define temp_sens_a A9
#define temp_sens_b A8
#define temp_sens_c A10
#define temp_sens_d A11

// Loop Timing
#define CONTROL_LOOP_RATE 10
#define SENSOR_UPDATE_RATE 200
#define DEBUG_RATE 500

#define GPSSerial Serial2

#define front_flip_threshold 30
#define back_flip_threshold -30
#define flip_correction_time 500
#define total_flip_time 1000
