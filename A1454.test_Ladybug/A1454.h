/*
 * Copyright (c) 2021 Tlera Corp.  All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal with the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 *  1. Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimers.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimers in the
 *     documentation and/or other materials provided with the distribution.
 *  3. Neither the name of Tlera Corp, nor the names of its contributors
 *     may be used to endorse or promote products derived from this Software
 *     without specific prior written permission.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
 * CONTRIBUTORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * WITH THE SOFTWARE.
 */

#ifndef A1454_h
#define A1454_h

#include <Arduino.h>
#include "I2CDev.h"
#include <Wire.h>

#define A1454_ADDRESS 			  0x60				//I2C Device Address

#define A1454_ACCESS_ADDRESS 	0x24				//Register which enables or disables customer write access to internal registers
#define A1454_ACCESS_CODE 		0x2C413534	//Access code - must be entered into the access register to gain write access to internal registers

#define A1454_TEMPOUT			    0x1D				//Stores temperature data  
#define A1454_OUTPUT			    0x1F				//Stores the magnetic field strength value 
#define A1454_SLEEP 			    0x20				//Stores the bit for setting/clearing SLEEP mode 

class A1454 
{
	public: 
		A1454(I2Cdev* i2c_bus); 		//Constructor1D		
		int16_t readMag(void);			//Read magnetometer value 
		int16_t readTemp(void);			//Read temperature value 
		uint8_t readMode(void); 		//Check for wake/sleep mode 
    void sleep(void);           //Put sensor into sleep mode 
    void wake(void);            //Wake sensor up from sleep mode 
    void access(void);
    private:
    I2Cdev* _i2c_bus;
};

#endif
