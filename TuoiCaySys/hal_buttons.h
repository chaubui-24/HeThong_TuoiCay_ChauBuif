#ifndef HAL_BUTTONS_H
#define HAL_BUTTONS_H

#include <stdbool.h>

void HAL_Buttons_Init(void);

bool HAL_Button1_Pressed(void);
bool HAL_Button2_Pressed(void);

#endif