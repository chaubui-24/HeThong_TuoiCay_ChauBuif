#include "hal_sensors.h"
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

static int seeded = 0;
static void ensure_seed(void)
{
    if (!seeded)
    {
        srand((unsigned)time(NULL));
        seeded = 1;
    }
}

void HAL_Sensors_Init(void)
{
    ensure_seed();
}

float HAL_ReadSoilMoisture_percent(void)
{
    ensure_seed();
    const int samples = 5;
    float sum = 0.0f;
    for (int i=0; i<samples; i++)
    {
        float v = 20.0f + (rand() % 501) / 10.0f;
        sum += v;
        usleep(2000);
    }
    float val = sum / samples;
    if (val < 0.0f)  val = 0.0f;
    if (val > 100.0f)  val = 100.0f;
    return val;
}

float HAL_ReadTemperature_C(void)
{
    ensure_seed();
    return 18.0f + (rand() % 171) / 10.0f;
}