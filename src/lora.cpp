#include <Arduino.h>
#include "LoRa_E32.h"
#include "def.h"

// Our LoRa instance
LoRa_E32 lora(&Serial, lora_AUX, lora_M0, lora_M1);


void printParameters(struct Configuration configuration)
{
  Serial.println("----------------------------------------");

  Serial.print(F("HEAD : "));
  Serial.print(configuration.HEAD, BIN);
  Serial.print(" ");
  Serial.print(configuration.HEAD, DEC);
  Serial.print(" ");
  Serial.println(configuration.HEAD, HEX);
  Serial.println(F(" "));
  Serial.print(F("AddH : "));
  Serial.println(configuration.ADDH, DEC);
  Serial.print(F("AddL : "));
  Serial.println(configuration.ADDL, DEC);
  Serial.print(F("Chan : "));
  Serial.print(configuration.CHAN, DEC);
  Serial.print(" -> ");
  Serial.println(configuration.getChannelDescription());
  Serial.println(F(" "));
  Serial.print(F("SpeedParityBit     : "));
  Serial.print(configuration.SPED.uartParity, BIN);
  Serial.print(" -> ");
  Serial.println(configuration.SPED.getUARTParityDescription());
  Serial.print(F("SpeedUARTDatte  : "));
  Serial.print(configuration.SPED.uartBaudRate, BIN);
  Serial.print(" -> ");
  Serial.println(configuration.SPED.getUARTBaudRate());
  Serial.print(F("SpeedAirDataRate   : "));
  Serial.print(configuration.SPED.airDataRate, BIN);
  Serial.print(" -> ");
  Serial.println(configuration.SPED.getAirDataRate());

  Serial.print(F("OptionTrans        : "));
  Serial.print(configuration.OPTION.fixedTransmission, BIN);
  Serial.print(" -> ");
  Serial.println(configuration.OPTION.getFixedTransmissionDescription());
  Serial.print(F("OptionPullup       : "));
  Serial.print(configuration.OPTION.ioDriveMode, BIN);
  Serial.print(" -> ");
  Serial.println(configuration.OPTION.getIODroveModeDescription());
  Serial.print(F("OptionWakeup       : "));
  Serial.print(configuration.OPTION.wirelessWakeupTime, BIN);
  Serial.print(" -> ");
  Serial.println(configuration.OPTION.getWirelessWakeUPTimeDescription());
  Serial.print(F("OptionFEC          : "));
  Serial.print(configuration.OPTION.fec, BIN);
  Serial.print(" -> ");
  Serial.println(configuration.OPTION.getFECDescription());
  Serial.print(F("OptionPower        : "));
  Serial.print(configuration.OPTION.transmissionPower, BIN);
  Serial.print(" -> ");
  Serial.println(configuration.OPTION.getTransmissionPowerDescription());

  Serial.println("----------------------------------------");
}

void updateLoraParameters()
{

  ResponseStructContainer c;
  c = lora.getConfiguration();
  Configuration configuration = *(Configuration *)c.data;
  configuration.ADDL = 3;
  configuration.ADDH = 0;
  configuration.CHAN = channels[selectedChannel];
  configuration.OPTION.fixedTransmission = FT_TRANSPARENT_TRANSMISSION;
  configuration.OPTION.wirelessWakeupTime = WAKE_UP_250;

  configuration.OPTION.fec = FEC_1_ON;
  configuration.OPTION.ioDriveMode = IO_D_MODE_PUSH_PULLS_PULL_UPS;
  configuration.OPTION.transmissionPower = POWER_10;

  configuration.SPED.airDataRate = AIR_DATA_RATE_010_24;
  configuration.SPED.uartBaudRate = UART_BPS_9600;
  configuration.SPED.uartParity = MODE_00_8N1;

  lora.setConfiguration(configuration, WRITE_CFG_PWR_DWN_SAVE);
  printParameters(configuration);
  c.close();
}

void changeLoraChannel()
{
  selectedChannel = (selectedChannel == 9) ? 0 : selectedChannel++;
  updateSevenSegmentDisplay(selectedChannel);
  updateLoraParameters();
  Serial.print("Changed channel to: ");
  Serial.println(selectedChannel);
}

void setupLora()
{
  lora.begin();
  updateLoraParameters();
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
      if (receivedState == 1 || receivedState == 2 || receivedState == 3)
      {
        Serial.print("Received state: ");
        Serial.println(receivedState);
        state = (state == receivedState) ? 0 : receivedState;
      }
    }
    else
    {
      Serial.println(rc.status.getResponseDescription());
    }
  }
}
