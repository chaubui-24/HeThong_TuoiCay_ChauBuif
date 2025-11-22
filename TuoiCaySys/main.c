#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

#include "config.h"
#include "spws_controller.h"
#include "hal_actuators.h"

static SystemState_t g_state;
static volatile int keep_running = 1;
static void sigint_handler(int s)
{
    (void)s;
    keep_running = 0;
}

static void init_defaults(SystemState_t *s)
{
    s->mode = MODE_AUTO;
    s->pumpState = PUMP_OFF;
    s->ledState = LED_NORMAL;
    s->settings.minMoistuneThreshold = 30.0f;
    s->settings.maxMoistureThreshold = 60.0f;
    s->settings.sensorReadInterval_s = 5;
    s->settings.maxWateringDuration_s = 20;
    s->settings.manualWateringDuration_s = 10;
    s->sensorData.soilMoisturePercent = 50.0f;
    s->sensorData.airTemperatureCelsius = 25.0f;
    s->wateringTimeCounter_s = 0;
    s->lastSensorReadTime_s = 0;
}

int main(void)
{
    signal(SIGINT, sigint_handler);
    init_defaults(&g_state);
    
    SPWS_Init(&g_state);

    printf("[MAIN] Chay vong lap chinh. Nhan Ctrl+C de thoat.\n");

    while (keep_running)
    {
        SPWS_RunOnce(&g_state, 1);
        sleep(1);
    }

    printf("[MAIN] Ket thuc: tat bom, LED ve binh thuong.\n");
    TurnPumpOff();
    HAL_SetLedState(LED_NORMAL);

    return 0;
}