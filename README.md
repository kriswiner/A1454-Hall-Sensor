# A1454-Hall-Sensor

Sketch for A1454 I2C Hall Effect sensor using a custom-made A1454 [breakout board](https://oshpark.com/shared_projects/NNIjeOuZ)
running on an STM32L432 (Ladybug) development board.
 
Sketch based on work by Laveréna Wienclaw for [TinyCircuits](https://github.com/TinyCircuits/TinyCircuits-A1454-library)
  
Sketch demonstrates putting the sensor in sleep mode and waking up from sleep mode, and
getting properly scaled signed 12-bit mag sensor and temperature sensor data.
  
Sensor breakout has resistor dividers on AD0 and AD1 allowing for many A1454 sensors
to be on the same I2C bus. Here the I2C address is set to 0x60.

![A1454](https://user-images.githubusercontent.com/6698410/120878195-a0845180-c56f-11eb-912b-9dd29f5823a6.jpg)
  
Copyright (c) 2021 Tlera Corp.  All rights reserved.
  
Unlimited distribution permitted with full attribution
