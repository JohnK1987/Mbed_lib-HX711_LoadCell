#include "Mbed_lib-HX711_LoadCell.h"
#include "mbed.h"
 
#define SCALE_VALUE 259.79 //multiple propre à chaque hardware
#define HX_DELAY 2 //us
 
ML_HX711_LoadCell::ML_HX711_LoadCell(PinName pinData, PinName pinSck, uint8_t gain):data(pinData),sck(pinSck)
{
    
    this->setGain(gain);
    sck = 1;        //Initialisation HX711
    wait_us(100);
    sck = 0;
    
    this->setOffset(averageValue(10)); //TARE de la balance
    this->setScale(SCALE_VALUE);        //Réglage du valeur du SCALE
}
 
ML_HX711_LoadCell::~ML_HX711_LoadCell()
{
 
}
 
int ML_HX711_LoadCell::averageValue(uint8_t times) //Calcule une moyenne sur plusieurs mesures 
{
    int sum = 0;
    for (int i = 0; i < times; i++)
    {
        sum += getValue();
    }
 
    return sum / times;
}
 
int ML_HX711_LoadCell::getValue() //Obtenir la valeur brut du controller
{
    int buffer; 
    buffer = 0 ;
    
    while (data.read()==1) //wait is ready
    ;
    
    for (uint8_t i = 24; i--;) //read 24 bit 1 per 1 and save to buffer
    {
        sck=1;
        wait_us(HX_DELAY);
        buffer = buffer << 1 ;
    
        if (data.read())
        {
            buffer ++;
        }
        
        sck=0;
        wait_us(HX_DELAY);
    }
    
    for (int i = 0; i < _gain; i++)
    {
        sck=1; 
        wait_us(HX_DELAY);
        sck=0;
        wait_us(HX_DELAY);
    }
    
    buffer = buffer ^ 0x800000;
 
    return buffer;
}
 
void ML_HX711_LoadCell::setOffset(int offset)
{
    _offset = offset;
}
 
void ML_HX711_LoadCell::setScale(float scale)
{
    _scale = scale;
}
 
float ML_HX711_LoadCell::getGram()
{
    long val = (averageValue(2) - _offset);
    return (float) val / _scale;
}
 
void ML_HX711_LoadCell::setGain(uint8_t  gain) 
{
    switch (gain) 
    { 
        case 128:       // channel A, gain factor 128 
            _gain = 1; 
            break; 
            
        case 64:        // channel A, gain factor 64 
            _gain = 3; 
            break; 
            
        case 32:        // channel B, gain factor 32 
            _gain = 2; 
            break; 
    } 
    sck = 0;
    getValue();
}
 
void ML_HX711_LoadCell::powerDown() 
{
    sck = 0;
    sck = 1;
}
 
void ML_HX711_LoadCell::powerUp() 
{
    sck = 0;
}
 
void ML_HX711_LoadCell::tare(uint8_t times) 
{
    int sum = averageValue(times);
    setOffset(sum);
}
            