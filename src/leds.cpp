#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "def.h"

Adafruit_NeoPixel strip(LEDCOUNT, LEDPIN, NEO_RGB + NEO_KHZ800);

bool flashed = false;

void setupNeopixels()
{
    strip.begin();
    strip.show();            // set all pixels to black
    strip.setBrightness(50); // Set brightness to about 1/5 (max = 255)
}

// flash a spcific pixel
void flashNeopixel(int pixel, int r, int g, int b)
{
    if (flashed) // if led is flashed
    {
        if ((millis() - lastExecutionMillis) >= NEOPIXEL_FLASH_ON_PERIOD_MS) // check if 1 second has passed
        {
            lastExecutionMillis = millis(); // set last flashing period
            strip.clear();                  // stop flashing led
            strip.show();
            flashed = false;
        }
    }
    else // if led is not flashed
    {
        if ((millis() - lastExecutionMillis) >= NEOPIXEL_FLASH_OFF_PERIOD_MS) // check if 3 seconds have passed
        {
            lastExecutionMillis = millis();                   // set last flashing period
            strip.setPixelColor(pixel, strip.Color(r, g, b)); // flash the led
            strip.show();
            flashed = true;
        }
    }
}

void flashStateLED()
{
    switch (state)
    {
    case 0:
        break;
    case 1:
        digitalWrite(LED_GREEN, !digitalRead(LED_GREEN));
        break;
    case 2:
        digitalWrite(LED_YELLOW, !digitalRead(LED_YELLOW));
        break;
    case 3:
        digitalWrite(LED_RED, !digitalRead(LED_RED));
        break;
    }
}