#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "def.h"

Adafruit_NeoPixel strip(LEDCOUNT, LEDPIN, NEO_RGB + NEO_KHZ800);

void setupNeopixels()
{
    strip.begin();
    strip.show();            // set all pixels to black
    strip.setBrightness(50); // Set brightness to about 1/5 (max = 255)
}

// flash a spcific pixel
void flashNeopixel(int pixel, int r, int g, int b)
{
    strip.setPixelColor(pixel, strip.Color(r, g, b));
    strip.show();
    // delay(500);
    strip.clear();
    strip.show();
    // delay(500);
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