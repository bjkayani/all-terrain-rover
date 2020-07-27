int rc_vals[4] = {0, 0, 0, 0}; //to store rc pulse values
int mapped_pwm_vals[2] = {0, 0}; //to store mapped pwm values
float motor_currents[4] = {0, 0, 0, 0}; //to store final motor current values
float motor_temps[4] = {0, 0, 0, 0}; //to store motor temperatures

long last_debug = 0;
long last_control_loop = 0;
long last_sensor_update = 0;
long current_time = 0;

int day = 0;
int month = 0;
int year = 0;
int second = 0;
int minute = 0;
int hour = 0;
double latitude = 0;
double longitude = 0;
double gps_speed = 0;
double altitude = 0;
double angle = 0;
int satellites = 0;
int gps_quality = 0;
boolean gps_fix = false;

float batt_voltage = 0;

float temp = 0;
float roll = 0;
float pitch = 0;
float heading = 0;

int flip_direction = 0;
long last_flip_time = 0;
long time_since_last_flip = 5000;

// moving average variables for the roll
const int roll_ma_num_readings = 5;
float roll_ma_readings[roll_ma_num_readings];      // the readings from the analog input
int roll_ma_readIndex = 0;
float roll_ma_total = 0;                  // the running total
float roll_ma = 0;                // the average

bool estop = true;
