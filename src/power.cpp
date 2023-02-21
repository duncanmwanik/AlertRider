#include <Arduino.h>
#include "def.h"

void checkBatteryVoltage()
{
    int batteryLevel = analogRead(BATTERY_VOLTAGE_PIN);
    // If battery voltage is low
    if (batteryLevel >= BATTERY_VOLTAGE_FULL)
    {
        flashNeopixel(2, 0, 255, 0); // flash green
    }
    else if (batteryLevel >= BATTERY_VOLTAGE_OKAY && batteryLevel < BATTERY_VOLTAGE_FULL)
    {
        flashNeopixel(2, 255, 255, 0); // flash yellow
    }
    else if (batteryLevel >= BATTERY_VOLTAGE_LOW && batteryLevel < BATTERY_VOLTAGE_OKAY)
    {
        flashNeopixel(2, 255, 0, 0); // flash red
    }
    else
    {
        // initiate sleep
    }
}