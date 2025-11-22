#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>
#include <stdbool.h>

typedef enum
{
    MODE_AUTO = 0, 
    MODE_MANUAL
} SystemMode_t;

typedef enum
{
    PUMP_OFF = 0,
    PUMP_ON
} PumpState_t;

typedef enum 
{
    LED_NORMAL = 0,
    LED_WATERING,
    LED_LOW_MOISTURE_ALERT,
    LED_ERROR
} LedState_t;

typedef struct 
{
    float minMoistuneThreshold;  /*soil < min: start watering*/
    float maxMoistureThreshold;  /*soil > max: stop ________*/
    unsigned int sensorReadInterval_s;
    unsigned int maxWateringDuration_s;
    unsigned int manualWateringDuration_s;
} SystemSetting_t;

typedef struct 
{
    float soilMoisturePercent;
    float airTemperatureCelsius;
} SensorData_t;

typedef struct 
{
    SystemMode_t mode;
    PumpState_t pumpState;
    LedState_t ledState;
    SystemSetting_t settings;
    SensorData_t sensorData;

    unsigned int wateringTimeCounter_s;
    unsigned int lastSensorReadTime_s;
} SystemState_t;

#endif 


