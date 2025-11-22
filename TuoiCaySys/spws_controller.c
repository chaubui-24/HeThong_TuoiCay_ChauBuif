#include "config.h"
#include "spws_controller.h"
#include "hal_sensors.h"
#include "hal_actuators.h"
#include "hal_buttons.h"
#include <stdio.h>
#include <time.h>

static unsigned int wateringStart_s = 0;
static unsigned int lastSensorRead_s = 0;
static int manualRequest = 0;

static unsigned int now_s(void)
{
    return (unsigned int)time(NULL);
}

void SPWS_Init(SystemState_t *state)
{
    HAL_Sensors_Init();
    HAL_Actuators_Init();
    HAL_Buttons_Init();

    wateringStart_s = 0;
    lastSensorRead_s = 0;
    manualRequest = 0;

    HAL_SetLedState(state->ledState);
    if (state->pumpState == PUMP_ON)
        TurnPumpOn();
    else TurnPumpOff();

    printf("[SPWS] Init complete. Mode=%s\n", state->mode == MODE_AUTO ? "AUTO" : "MANUAL");
}

static void read_sensors(SystemState_t *state)
{
    float soil = HAL_ReadSoilMoisture_percent();
    float t = HAL_ReadTemperature_C();
    state->sensorData.soilMoisturePercent = soil;
    state->sensorData.airTemperatureCelsius = t;
    printf("[SENSOR] Soil=%.2f%%, Temp=%.2fC\n", soil, t);
}

static void start_watering(SystemState_t *state)
{
    if (state->pumpState == PUMP_OFF)
    {
        TurnPumpOn();
        state->pumpState = PUMP_ON;
        wateringStart_s = now_s();
        HAL_SetLedState(LED_WATERING);
        printf("[EVENT] Bat dau tuoi\n");
    }
}

static void stop_watering(SystemState_t *state)
{
    if (state->pumpState == PUMP_ON)
    {
        TurnPumpOff();
        state->pumpState = PUMP_OFF;
        wateringStart_s = 0;
        HAL_SetLedState(LED_NORMAL);
        printf("[EVENT] Dung tuoi\n");
    }
}

void SPWS_RunOnce(SystemState_t *state, unsigned int elapsed_s)
{
    unsigned int now = now_s();

    if (HAL_Button1_Pressed())
    {
        if (state->mode == MODE_AUTO)
        {
            state->mode = MODE_MANUAL;
            stop_watering(state);
            printf("[BUTTON] Chuyen sang MANUAL\n");
        }
        else
        {
            state->mode = MODE_AUTO;
            printf("[BUTTON] Chuyen sang AUTO\n");
        }
    }
    if (HAL_Button2_Pressed())
    {
        if (state->mode == MODE_MANUAL)
        {
            manualRequest = 1;
            printf("[BUTTON] Yeu cau tuoi thu cong\n");
        }
        else
        {
            printf("[BUTTON] Nut 2 chi hoat dong o MODE_MANUAL\n");
        }
    }

    if (now - lastSensorRead_s >= state->settings.sensorReadInterval_s)
    {
        read_sensors(state);
        lastSensorRead_s = now;
    }

    if (state->mode == MODE_AUTO)
    {
        if (state->sensorData.soilMoisturePercent < state->settings.minMoistuneThreshold)
        {
            start_watering(state);
        }
    }

    if (manualRequest && state->mode == MODE_MANUAL)
    {
        start_watering(state);
        wateringStart_s = now;
        manualRequest = 0;
    }

    if (state->pumpState == PUMP_ON)
    {
        if (state->sensorData.soilMoisturePercent > state->settings.maxMoistureThreshold)
        {
            printf("[LOGIC] Moisture %.2f > max %.2f ->  stop\n",
                   state->sensorData.soilMoisturePercent, state->settings.maxMoistureThreshold);
            stop_watering(state);
            return;
        }

        if (wateringStart_s != 0)
        {
            unsigned int elapsed = now - wateringStart_s;
            unsigned int allowed = (state->mode == MODE_MANUAL) ? state->settings.manualWateringDuration_s :
                                                                  state->settings.maxWateringDuration_s;
            if (elapsed >= allowed)
            {
                printf("[LOGIC] Thoi gian tuoi %u s >= %u s -> stop\n", elapsed, allowed);
                stop_watering(state);
                return;
            }
        }
    }

    if (state->sensorData.airTemperatureCelsius > 60.0f || state->sensorData.airTemperatureCelsius < -20.0f)
    {
        HAL_SetLedState(LED_ERROR);
    }
}