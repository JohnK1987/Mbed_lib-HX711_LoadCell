/*
 * FILE: Mbed_lib-HX711_LoadCell.h and .cpp
 * 
 * VERSION: 0.1
 * PURPOSE: HX711 weight library for Nucleo STM32
 * AUTHOR: Bertrand Bouvier
 * LICENSE: GPL v3 (http://www.gnu.org/licenses/gpl.html)
 *
 * DATASHEET: http://www.dfrobot.com/image/data/SEN0160/hx711_english.pdf
 * URL: 
 *
 * HISTORY:
 * - 24/05/2015 - Bertrand Bouvier - Original version
 * - 20.12.2023 - Jan Kamidra
 *   Add short delay to read function because of high performance targets are too fast
 *   Rework access to pins. Were created in every function again and again.
 *   Library was renamed to be clear it is library for Mbed and for a Load cell not just general ADC.
 *
 * SPECIAL THANKS:
 *  Inspiré du travail de Weihong Guan (@aguegu)
 *  https://github.com/aguegu/Arduino
 *  http://aguegu.net
 *  
 *  Inspiré du travail de bodge
 *  https://github.com/bogde/HX711
 *
 */
 
#ifndef ML_HX711_LOADCELL_H
#define ML_HX711_LOADCELL_H
 
#include "mbed.h"
 
 
class ML_HX711_LoadCell
{
 
public:
    ML_HX711_LoadCell(PinName pinData, PinName pinSck,uint8_t gain = 128);
    ~ML_HX711_LoadCell();
    int getValue(void);
    int averageValue(uint8_t times);
    void setOffset(int offset);
    void setScale(float scale);
    float getGram();
    void setGain(uint8_t gain);
    void powerDown();
    void powerUp();
    void tare(uint8_t times = 10);
 
 
private:
    DigitalOut sck;
    DigitalIn data;
    int _offset;
    float _scale;
    uint8_t _gain; //[128|32|64]
};
 
#endif 