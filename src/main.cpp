#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "LoRa_E32.h"
#include "def.h"

// TODO : Add delays using millis()
// TODO : check voltage and flash neopixels periodically

void setup()
{
  Serial.begin(115200);

  initializePins();

  setupLora();

  setupNeopixels();

  updateSevenSegmentDisplay(0); // display the default channel on the seven-segment
}

void loop()
{
  checkBatteryVoltage();   // check battery voltage and flash the addressable led
  checkForButtonPress();   // check if any button has been pressed
  flashStateLED();         // flash specific LED only if state is 1, 2 or 3
  checkIncomingLoraData(); // check for data/state send from other Loras
}
