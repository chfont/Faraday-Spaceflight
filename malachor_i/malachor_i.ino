#include <Wire.h>
#include <SPI.h>
#include <Servo.h>
#include <Adafruit_BMP280.h>
#include "I2Cdev.h"
#include "MPU6050.h"
#include "flash.h"
#include "constDefinitions.h"
#include "sd_ops.h"
#include <PID_v1.h>
//Declare BMP
Adafruit_BMP280 bmp;
float pressure;
float temperature;
float init_pressure;

//IMU
MPU6050 mpu;
int16_t acc[3];
int16_t gyro[3];
int16_t init_gyro[3]; //Need initial configuration in order to determine the orientation
#define OUTPUT_READABLE_ACCELGYRO

const int chipSelect = 0; //Pin on teensy

//SPI Flash Chip 
#define CHIPSIZE MB64
SPIFlash flash(1); //pin 1 is flash chip

uint32_t dataWritten = 0; 
bool done, ignite;

Servo tvcXServo;
Servo tvcZServo;

//Counter to hold phase
short phase;

//PID Controller
double zero_x, zero_z, err_x, err_z, x_input, z_input;
PID pid_x(&x_input, &err_x, &zero_x, KPX,KIX,KDX, DIRECT);
PID pid_z(&z_input, &err_z, &zero_z, KPZ,KIZ,KDZ, DIRECT);

void setup() {
  // put your setup code here, to run once:
  done, ignite = false;
  phase = 0;
  //0. TURN ON LIGHTS
  pinMode(redLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  digitalWrite(redLED, HIGH);
  digitalWrite(blueLED, LOW);
  digitalWrite(greenLED, LOW);

  pinMode(pyro1, OUTPUT);
  pinMode(pyro2, OUTPUT);
  pinMode(pyro3, OUTPUT);
  pinMode(pyro4, OUTPUT);
  digitalWrite(pyro1, LOW);
  digitalWrite(pyro2, LOW);
  digitalWrite(pyro3, LOW);
  digitalWrite(pyro4, LOW);
  
  //1. TURN ON SENSORS: BMP AND MPU
  //Serial.begin()?
  bmp.begin();
  mpu.initialize();
  init_pressure = bmp.readPressure();
  
  //2. TURN ON FLASH CHIP
  flash.begin(CHIPSIZE);
  flash.setClock(133);

  //3. GET INITIAL GYRO DATA
  mpu.getMotion6(&acc[0], &acc[1], &acc[2], &init_gyro[0], &init_gyro[1], &init_gyro[2]);
  zero_x = init_gyro[0];
  zero_z = init_gyro[2];
  
  //IGNITE
  delay(12000);
  digitalWrite(pyro3, HIGH);
  delay(5000);
  digitalWrite(pyro3, LOW);
}

void writeMPUToFlash(){
  dataWritten += writeShortArrToFlash(flash, acc, 3);
  dataWritten += writeShortArrToFlash(flash, gyro, 3);
}

void writeBMPToFlash(){
  dataWritten += writeFloatToFlash(flash, pressure);
  dataWritten += writeFloatToFlash(flash, temperature);
}


//Phases: going up 1, going up 2, apex, falling, done
void loop() {
  // put your main code here, to run repeatedly:
  if(phase == 0 && abs(pressure-init_pressure) > ERROR_GROUND){
    phase = 1;
  }
  if(phase < 4){
    //Get DATA
    mpu.getMotion6(&acc[0], &acc[1], &acc[2], &gyro[0],&gyro[1], &gyro[2]);
    pressure = bmp.readPressure();
    temperature = bmp.readTemperature();

    //REACT TO DATA: Y Positive means falling, due to orientation of MPU
    if(acc[1] > 0){
      phase = 3;
    }
    //WRITE TO FLASH CHIP
    writeMPUToFlash();
    writeBMPToFlash();
    if(phase==3 && abs(pressure-init_pressure) < ERROR_IGNITE && pressure > MIN_PRESSURE){
      digitalWrite(pyro1, HIGH);
      delay(5000);
      digitalWrite(pyro1, LOW);
      ignite = true;
    }
    
    if(phase == 3 && abs(pressure-init_pressure) < ERROR_GROUND){
      //STOP 
      phase = 4;
      flash.writeLong(0x7FFFFC, dataWritten);
      //TODO: Implement copying from flash chip to sd card, once code for each is verified via tests
    }

    //TVC algorithm
    if(phase > 0 && phase < 3){
      x_input = gyro[0];
      z_input = gyro[2];
      pid_x.Compute();
      pid_z.Compute();
      //modify zero point
      zero_x = x_input;
      zero_z = z_input;

      //move servos to account for error
      tvcXServo.write(tvcXServo.read()+(err_x * 180.0 / PI));
      tvcZServo.write(tvcZServo.read()+(err_z *180.0 / PI));
    }

  }
  
}
