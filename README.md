Library for interfacing HX711 with a Load cell under Mbed OS(mainly for version 6+).
It is probably a port from Arduino ECO.

Example:
```
#include "mbed.h"
#include "ML_HX711_LoadCell.h"

ML_HX711_LoadCell scale(PB_8, PB_9); 

float calibration_factor = -702; // a default value
int averageSamples = 100;

int main(void)
{
    printf("HX711 calibration sketch\n");
    printf("Remove all weight from scale\n");
    printf("After readings begin, place known weight on scale\n\n");
    printf("If you see incorrect weight, then use math Rule of three for calculation of correct calibration factor value\n");

    scale.setScale(0);
    scale.tare(); //Reset the scale to 0
    
    while (true) {
        scale.setScale(calibration_factor); //Adjust to this calibration factor
        float weight = scale.getGram();
        printf("Weight: %.2fg, calib: %.2f\n", weight,calibration_factor);
        thread_sleep_for(1000);
    }
}
```

Jan Kamidra 20.12.2023
