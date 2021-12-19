/**
*  Arduino Library for Texas Instruments DAC121S101 - 12-Bit Micro Power, RRO Digital-to-Analog Converter
*  
*  @author Dan Maslach <dmaslach@gmail.com>
*/

/**
 * The MIT License
 *
 * Copyright 2021 Dan Maslach <dmaslach@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "DAC121S101.h"
#include <Arduino.h>


/*
 * Constructor of the class
 * @param io_pin_cs a byte indicating the pin to be use as the chip select pin (CS)
 */
DAC121::DAC121(uint8_t io_pin_cs) {
    cs = io_pin_cs;
   }

/*
 * This method initializes the SPI port and sets default state to normal mode and data to an initial setpoint;
 */
void DAC121::begin(uint8_t mode, uint16_t initData, float refVolts) {
    vRef = refVolts;
    SPI.begin();
    modeSet = mode;
    setData(initData);

}

/*
 * This method just made to set the mode globally for the chip
 */
void DAC121::setPowerDownMode(uint8_t mode) {
     modeSet = mode;

}

/*
 * This sets the DAC to your preferred voltage using a given reference voltage (read from an IC's analog input) so it can set the step as close to your given set voltage
 */

void DAC121::setVoltage(float setVolts, float vRef) {
    uint16_t digiVolts = round((setVolts * 4096) / vRef);
    setData(digiVolts);
}

/*
 * This sends the data via SPI. Takes the mode previously set, and data and sends it.
 */

void DAC121::setData(uint16_t data) {  

	// If the setPt is out of range, clamp it
	if (data > 4095) {
		data = 4095;
	} else if (data < 0) {
		data = 0;
	}


    uint16_t maskedMode = (modeSet << 12) & PDM_MASK;
	uint16_t maskedData = data & DATA_MASK;

    uint16_t sendData = maskedMode | maskedData;     
  
    uint8_t byteLow = sendData & 0xff;
    uint8_t byteHigh = (sendData >> 8);
     SPI.beginTransaction(SPISettings(SCLK, MSBFIRST, SPI_MODE3));
    
    // Send config
    digitalWrite(cs, LOW);
    delay(100);
    SPI.transfer(byteHigh);
    SPI.transfer(byteLow);
    delay(5);
    digitalWrite(cs, HIGH);
    delay(100);
    
    SPI.endTransaction();

}
