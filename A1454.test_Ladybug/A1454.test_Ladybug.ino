/*************************************************************************
 * Sketch for A1454 I2C Hall Effect sensor using a custom-made A1454 breakout board
 * running on an STM32L432 (Ladybug) development board.
 * 
 *  Written by Kris Winer June 4, 2021
 *  
 * Sketch based on work by Laveréna Wienclaw for TinyCircuits. See:
 * 
 * https://github.com/TinyCircuits/TinyCircuits-A1454-library/blob/master/src/TinyCircuits_A1454.h
 * 
 * Sketch demonstrates putting the sensor in sleep mode and waking up from sleep mode, and
 * getting properly scaled signed 12-bit mag sensor and temperature sensor data.
 * 
 * Sensor breakout has resistor dividers on AD0 and AD1 allowing for many A1454 sensors
 * to be on the same I2C bus. Here the I2C address is set to 0x60.
 * 
 * Copyright (c) 2021 Tlera Corp.  All rights reserved.
 * 
 * Unlimited distribution permitted with full attribution
 * 
 ************************************************************************/
 
#include "I2CDev.h"
#include "A1454.h"  

#define I2C_BUS    Wire               // Define the I2C bus (Wire instance) you wish to use

I2Cdev             i2c_0(&I2C_BUS);   // Instantiate the I2Cdev object and point to the desired I2C bus

// A1454 configuration
float mscale = 4.0f;  // scale is either 2 or 4 depending on the A1454 variant

uint8_t mode = 0;
int16_t mag, temp;
float tempC, tempF;

// A sensor object, the methods will be used to interface with the A1454
 A1454 hall =  A1454(&i2c_0);


void setup() 
{
  Serial.begin(115200);
  delay(4000);
  Serial.println("Serial begin!");
  
  I2C_BUS.begin();                // Set master mode, default on SDA/SCL for STM32L4
  I2C_BUS.setClock(400000);       // I2C frequency at 400 kHz
  delay(100);

  Serial.println("Scan for I2C devices:");
  i2c_0.I2Cscan();                // should detect A1494 at 0x60
  delay(100);

  //hall.access();

  // Check wake/sleep performance
  hall.sleep();  
  delay(100);
  mode = hall.readMode();
  if (mode == 0) Serial.println("AWAKE\t\t");
  else if (mode == 1) Serial.println("SLEEPING\t\t");
  delay(1000);
  
  hall.wake(); //default is awake at power-on
  delay(100);
  mode = hall.readMode();
  if (mode == 0) Serial.println("AWAKE\t\t");
  else if (mode == 1) Serial.println("SLEEPING\t\t");
  delay(1000);
}

void loop() 
{
  mag  = hall.readMag();
  temp = hall.readTemp();

  Serial.print("Mag: ");
  Serial.print((float)mag / mscale/ 10.0f); // convert to ENOB, and Gauss to milliTesla
  Serial.print("mT"); // millitesla
  Serial.print('\t');

  tempC = (float)(temp)/ 8.0f + 25.0f; // convert to Centigrade
  Serial.print("TempC: ");
  Serial.print(tempC, 1);
  Serial.print("°C");
  Serial.print('\t');
  
  Serial.print("TempF: ");
  tempF = ((tempC * 1.8f) + 32.0f);
  Serial.print(tempF, 1);
  Serial.print("°F");
  Serial.println('\t');

  delay(500);
}
