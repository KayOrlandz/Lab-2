/*
  Serial-WR

  
*/

#include<Wire.h>
#define BUZZER 11

// LED status
//int led_status = HIGH;
int incomingByte = 0;
// Arduino pin numbers
//const int SW_pin = 2; // digital pin connected to switch output
const int X_pin = 0; // analog pin connected to X output
const int Y_pin = 1; // analog pin connected to Y output

const int MPU_addr=0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;


// the setup routine runs once when you press reset:
void setup() {
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  pinMode(BUZZER,OUTPUT);
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // initialize digital pin LED_BUILTIN as an output.
  //pinMode(LED_BUILTIN, OUTPUT);
  //digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  //led_status = HIGH;
}

// the loop routine runs over and over again forever:
void loop() {
  
  // read from the Serial port:
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  Serial.println(AcX);
  Serial.println(AcY);
  Serial.println(AcZ);
//  Serial.print(" | Tmp = "); Serial.println(Tmp/340.00+36.53);  //equation for temperature in degrees C from datasheet
//  Serial.print(" | GyX = "); 
  Serial.println(GyX);
//  Serial.print(" | GyY = "); 
  Serial.println(GyY);
//  Serial.print(" | GyZ = "); Serial.println(GyZ);
//  Serial.println();
  Serial.println(analogRead(X_pin));
  Serial.println(analogRead(Y_pin));
  digitalWrite(BUZZER,LOW);
  
  if (Serial.available() > 0) {
    // read the incoming byte: (when apple is eaten)
    incomingByte = Serial.read();
    //Serial.println(incomingByte);
    
    if(incomingByte == 'E') {
      // turn on Buzzer
      digitalWrite(BUZZER,HIGH);
    }
  }

  
  delay(175);

}
