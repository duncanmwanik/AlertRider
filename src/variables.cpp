#include <Arduino.h>
#include "def.h"

// keeps track of the button pressed
int state = 0; // GREEN = 1 , YELLOW = 2 , RED = 3

// keeps track of the selected channel for LORA
int selected_channel = 0;

// channels ----- { 0     1     2     3     4     5     6     7     8     9  }
int channels[] = {0x02, 0x04, 0X06, 0x08, 0x0A, 0x0B, 0x0C, 0x0E, 0x0F, 0x10};

// keeps track of time from millis()
long currentMillis = 0;