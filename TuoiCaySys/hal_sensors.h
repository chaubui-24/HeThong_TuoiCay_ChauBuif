#ifndef HAL_SENSORS_H
#define HAL_SENSORS_H

#include "config.h"


void HAL_Sensors_Init(void);

/*read %do am dat*/
float HAL_ReadSoilMoisture_percent(void);

/*read degree C*/
float HAL_ReadTemperature_C(void);

#endif
