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

#ifndef DAC121_h
#define DAC121_h

#include <Arduino.h>
#include <SPI.h>


#define DATA_MASK       0b0000111111111111
#define PDM_MASK		0b11 << 12
#define PDM_BIT_1_POS	14
#define PDM_BIT_0_POS	13

#define PDM_NORMAL		0b00
#define PDM_2_5K_GND	0b01
#define PDM_100K_GND	0b10
#define PDM_HIGH_IMP	0b11

/*
 * Class representing the DAC121 sensor chip
 */
class DAC121 {
    public:
        DAC121(uint8_t io_pin_cs);                                 ///< Constructor

        void begin(uint8_t mode, uint16_t initData, float refVolts);

        void setData(uint16_t data);
        void setVoltage(float setVolts, float Vref);
        void setPowerDownMode(uint8_t mode);      
        // Bit constant
        const long int SCLK        = 10000000;       ///< DAC121 SCLK frequency: 30000000 Hz Maximum for DAC121 (30Mhz)

       
    private:
        uint8_t cs;                                 ///< Chip select pin (choose one)
        uint8_t modeSet;
        float vRef = 3;
    
};

#endif
