#include <Servo.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>
#include "I2Cdev.h"
#include "MPU6050.h"
#include "mandragoraConstants.h"

//BMP Sensor and Data Definitions
Adafruit_BMP280 bmp;

float pressure;
float temperature;
float init_pressure;

//MPU Definitions
MPU6050 mpu;
int16_t acc_y; // y-axis acceleration
#define OUTPUT_READABLE_ACCELGYRO

int16_t phase_counter;
bool deployed;
void setup() {

  //SETUP AND TURN OFF IGNITE AND PARACHUTE PINS
  pinMode(IGNITE_PIN, OUTPUT);
  pinMode(PARACHUTE_PIN, OUTPUT);
  digitalWrite(IGNITE_PIN,LOW);
  digitalWrite(PARACHUTE_PIN,LOW);
  
  //Zero out values
  phase_counter = 0;
  deployed = 0;

  //Start up sensors
  bmp.begin();
  mpu.initialize();

  //Wait for sensors, then read initial pressure
  delay(50);
  init_pressure = bmp.readPressure();

  digitalWrite(IGNITE_PIN, HIGH);
  delay(PYRO_DELAY);
  digitalWrite(IGNITE_PIN, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  pressure = bmp.readPressure();
  acc_y = mpu.getAccelerationY();
  //Successful launch
  if(phase_counter == 0 && abs(pressure - init_pressure) >= SUCCESSFUL_LAUNCH_ALTITUDE){
    phase_counter = 1;
  }

  //Falling, so enter phase 2
  if(phase_counter == 1 && acc_y > 0){
    phase_counter = 2;
  }

  //Deploy Parachute
  if(phase_counter == 2 && abs(pressure-init_pressure) <= PARACHUTE_ALTITUDE && !deployed){
    deployed = 1;
    
    digitalWrite(PARACHUTE_PIN, HIGH);
    delay(PYRO_DELAY);
    digitalWrite(PARACHUTE_PIN,LOW);
  }
}
