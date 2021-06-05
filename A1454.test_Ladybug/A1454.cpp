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

#include "A1454.h"
#include "I2CDev.h"

//Constructor 
 A1454:: A1454(I2Cdev* i2c_bus) 
{
    _i2c_bus = i2c_bus;
}


//Read the 12-bit signed Magnetic Field Value 						
int16_t A1454::readMag() { 
	 uint8_t rawData[4] = {0, 0, 0, 0};  // mag data bytes stored here
   int16_t destination = 0;
   _i2c_bus->readBytes(A1454_ADDRESS, A1454_OUTPUT, 4, &rawData[0]);  // Read the 4 raw data registers  
   destination = (int16_t) (( (int16_t) (rawData[2] & 0x0F) << 12) | rawData[3] << 4); 
	 destination = destination >> 4;
	 return destination; 												
}


//Read the 12-bit signed Junction Temperature Value 
int16_t A1454::readTemp() {
   uint8_t rawData[4]= {0, 0, 0, 0};  // temp data bytes stored here
   int16_t destination=0;
   _i2c_bus->readBytes(A1454_ADDRESS, A1454_TEMPOUT, 4, &rawData[0]);  // Read the 4 raw data registers  
   destination = (int16_t) (( (int16_t) (rawData[2] & 0x0F) << 12) | rawData[3] << 4); 
   destination = destination >> 4;
	 return destination; 												
}


//Put the sensor into sleep mode 
void  A1454::sleep(void) {
    uint8_t rawData[4] = {0x00, 0x00, 0x00, 0x01};  // sleep bytes
   _i2c_bus->writeBytes(A1454_ADDRESS, A1454_SLEEP, 4, &rawData[0]);  // Write sleep bit                                                                     
}


//Wake the sensor from sleep mode, wait for it to stabilize 
void A1454::wake(void) {
    uint8_t rawData[4] = {0x00, 0x00, 0x00, 0x00};  // sleep bytes
   _i2c_bus->writeBytes(A1454_ADDRESS, A1454_SLEEP, 4, &rawData[0]);  // Clears the sleep bit 
   delay(1);                                    
}


void A1454::access(void) {
    uint8_t rawData[4] = {0x2C, 0x41, 0x35, 0x34};  // sleep bytes
   _i2c_bus->writeBytes(A1454_ADDRESS, A1454_ACCESS_ADDRESS, 4, &rawData[0]);  // Clears the sleep bit 
   delay(1);                                    
}


//Check awake or sleep status 
uint8_t A1454::readMode(void) {
   uint8_t rawData[4]= {0, 0, 0, 0};  // temp data bytes stored here
   _i2c_bus->readBytes(A1454_ADDRESS, A1454_SLEEP, 4, &rawData[0]);  // Read the 4 raw data registers  
   return rawData[3]; 											
}
