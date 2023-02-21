#include <Arduino.h>
#include "def.h"

void checkForButtonPress()
{
    if (!digitalRead(BUTTON_GREEN))
    {
        state = (state != 1) ? 1 : 0;
        sendLoraData(state);
    }
    if (!digitalRead(BUTTON_YELLOW))
    {
        state = (state != 2) ? 2 : 0;
        sendLoraData(state);
    }
    if (!digitalRead(BUTTON_RED))
    {
        state = (state != 3) ? 3 : 0;
        sendLoraData(state);
    }
    if (!digitalRead(BUTTON_CHANNEL))
    {
        changeLoraChannel();
    }
}
