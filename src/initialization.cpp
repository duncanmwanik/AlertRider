#include <Arduino.h>
#include "def.h"

void initializePins()
{
    pinMode(pinA, OUTPUT);
    pinMode(pinB, OUTPUT);
    pinMode(pinC, OUTPUT);
    pinMode(pinD, OUTPUT);
    pinMode(pinE, OUTPUT);
    pinMode(pinF, OUTPUT);
    pinMode(pinG, OUTPUT);
    pinMode(BUTTON_GREEN, INPUT_PULLUP);
    pinMode(BUTTON_YELLOW, INPUT_PULLUP);
    pinMode(BUTTON_RED, INPUT_PULLUP);
    pinMode(BUTTON_CHANNEL, INPUT_PULLUP);
}