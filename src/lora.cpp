#include <Arduino.h>
#include "LoRa_E32.h"
#include "def.h"

// Our LoRa instance
LoRa_E32 lora(&Serial1, lora_AUX, lora_M0, lora_M1);

void setupLora()
{
  lora.begin();
}

// sends state of the button pressed to other LoRas
void sendLoraData(int state)
{
  String data = String(state);
  ResponseStatus rs = lora.sendBroadcastFixedMessage(channels[selectedChannel], data);
  if (rs.code == 1) // if there's no error
  {
    Serial.print("Successfully sent state: ");
    Serial.println(data);
  }
  else
  {
    Serial.print("Failed to send state!");
    Serial.println(rs.getResponseDescription());
  }
}

// receives button states from other LoRas
void checkIncomingLoraData()
{
  int receivedState = 0;
  if (lora.available() > 1)
  {
    ResponseContainer rc = lora.receiveMessage();
    if (rc.status.code == 1) // if there's no error
    {
      receivedState = rc.data.toInt();
      if (receivedState == 1 || receivedState == 1 || receivedState == 1)
      {
        state = receivedState;
        Serial.print("Received state: ");
        Serial.println(state);
      }
    }
    else
    {
      Serial.println(rc.status.getResponseDescription());
    }
  }
}

void changeLoraChannel()
{
  selectedChannel = (selectedChannel == 9) ? 0 : selectedChannel++;
  updateSevenSegmentDisplay(selectedChannel);
  Serial.print("Changed channel to: ");
  Serial.println(selectedChannel);
}