# A1454-Hall-Sensor

Sketch for A1454 I2C Hall Effect sensor using a custom-made A1454 breakout board
running on an STM32L432 (Ladybug) development board.
 
Sketch based on work by Laveréna Wienclaw for [TinyCircuits](https://github.com/TinyCircuits/TinyCircuits-A1454-library/blob/master/src/TinyCircuits_A1454.h)
  
Sketch demonstrates putting the sensor in sleep mode and waking up from sleep mode, and
getting properly scaled signed 12-bit mag sensor and temperature sensor data.
  
Sensor breakout has resistor dividers on AD0 and AD1 allowing for many A1454 sensors
to be on the same I2C bus. Here the I2C address is set to 0x60.
  
Copyright (c) 2021 Tlera Corp.  All rights reserved.
  
Unlimited distribution permitted with full attribution
