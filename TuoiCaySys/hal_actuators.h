#ifndef HAL_ACTUATORS_H
#define HAL_ACTUATORS_H

#include "config.h"

void HAL_Actuators_Init(void);

void TurnPumpOn(void);
void TurnPumpOff(void);

void HAL_SetLedState(LedState_t);

#endif