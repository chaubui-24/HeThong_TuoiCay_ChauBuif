#include "hal_actuators.h"
#include <stdio.h>

static LedState_t currentLed = LED_NORMAL;
static int pumpOn = 0;

void HAL_Actuators_Init(void)
{
    currentLed = LED_NORMAL;
    pumpOn = 0;
    printf("[ACT] Actuators init: LED NORMAL, Pump OFF\n");
}

void TurnPumpOn(void)
{
    if (!pumpOn)
    {
        pumpOn = 1;
        printf("[ACT] Pump ON\n");
    }
}

void TurnPumpOff(void)
{
    if (pumpOn)
    {
        pumpOn = 0;
        printf("[ACT] Pump OFF\n");
    }
}

void HAL_SetLedState(LedState_t state)
{
    if (state != currentLed)
    {
        currentLed = state;
        switch (state)
        {
        case LED_NORMAL: printf("[LED] XANH - Binh thuong\n"); break;
        case LED_WATERING: printf("[LED] VANG - Dang tuoi\n"); break;
        case LED_LOW_MOISTURE_ALERT: printf("[LED] Do nhap nhay - Do am thap\n"); break;
        case LED_ERROR: printf("[LED] Do - Loi he thong\n"); break;
        default: break;
        }
    }
}