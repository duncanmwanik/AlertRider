// #include "Arduino.h"
// #include <Adafruit_NeoPixel.h>
// #include "LoRa_E32.h"

// // Pin 2-8 is connected to the 7 segments of the display.
// #define LEDPIN PA5 // ADDRESSABLE LED
// #define LEDCOUNT 3
// // BUTTONS
// #define BUTTONPIN1 PA4
// #define BUTTONPIN2 PA3
// #define BUTTONPIN3 PA2
// #define BUTTONPIN4 PA1
// // END
// // 7 SEGMENT DISPLAY
// #define pinA PB9
// #define pinB PB10
// #define pinC PB11
// #define pinD PB12
// #define pinE PB13
// #define pinF PB14
// #define pinG PB15
// // END
// // LORA MODULE EBYTE PINS
// #define lora_TX PA9  // ADD INTERNAL PULLUP
// #define lora_RX PA10 // ADD INTERNAL PULLUP
// #define lora_AUX PB5 // KEEP FLOAING/ HIGH IMPEDANCE INPUT WITH NO CONNECTION TO GND OR PWR
// #define lora_M1 PB3  // PULL TO GND FOR NORMAL OPERATION OF BYTE
// #define lora_M0 PB4  // PULL TO GND FOR NORMAL OPERATION OF BYTE
// // END

// // LORA DECLERATIONS
// LoRa_E32 e32ttl100(&Serial1, lora_AUX, lora_M0, lora_M1);

// // #define FREQUENCY_433
// // #define FREQUENCY_170
// // #define FREQUENCY_470
// #define FREQUENCY_868
// // #define FREQUENCY_915

// // END
// uint8_t state = 10;
// uint8_t stateRef = 10;
// uint8_t counter = 0;
// long currTime = 0;
// uint8_t s = 0;
// char sendBuffer[2] = "";
// uint8_t sendFlag = 0;

// // channels  arrat   { 0     1    2    3    4    5    6    7    8    9  }
// uint8_t NETWORKID = 0; // Must be the same for all nodes
// uint8_t channels[] = {0x02, 0x04, 0X06, 0x08, 0x0A, 0x0B, 0x0C, 0x0E, 0x0F, 0x10};
// int channel_selected = NETWORKID;

// Adafruit_NeoPixel strip(LEDCOUNT, LEDPIN, NEO_RGB + NEO_KHZ800);

// // Addresses for this node. CHANGE THESE FOR EACH NODE!

// char MYNODEID = 1;   // My node ID
// #define TONODEID 255 // Destination node ID
// #define FREQUENCY RF69_868MHZ
// // AES encryption (or not):

// #define ENCRYPT false                 // Set to "true" to use encryption
// #define ENCRYPTKEY "TOPSECRETPASSWRD" // Use the same 16-byte key on all nodes

// // Use ACKnowledge when sending messages (or not):

// #define USEACK true // Request ACKs or not

// // RFM69 radio;

// // PROTOTYPES
// void printParameters(struct Configuration configuration);
// void updateLoraParameters(int channel_selected);
// void sevensegment(uint8_t num);
// // END
// //  the setup routine runs once when you press reset:
// void setup()
// {

//     Serial.begin(115200);
//     Serial.print("Node ");
//     Serial.print(MYNODEID, DEC);
//     Serial.println(" ready");
//     // BEGIN LORA E32
//     e32ttl100.begin();
//     ///////////////
//     updateLoraParameters(channel_selected);
//     // initialize the digital pins as outputs.
//     pinMode(pinA, OUTPUT);
//     pinMode(pinB, OUTPUT);
//     pinMode(pinC, OUTPUT);
//     pinMode(pinD, OUTPUT);
//     pinMode(pinE, OUTPUT);
//     pinMode(pinF, OUTPUT);
//     pinMode(pinG, OUTPUT);
//     pinMode(BUTTONPIN1, INPUT_PULLUP);
//     pinMode(BUTTONPIN2, INPUT_PULLUP);
//     pinMode(BUTTONPIN3, INPUT_PULLUP);
//     pinMode(BUTTONPIN4, INPUT_PULLUP);
//     sevensegment(0);
//     strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
//     strip.show();            // Turn OFF all pixels ASAP
//     strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
// }

// // the loop routine runs over and over again forever:
// void loop()
// {
//     switch (s)
//     {
//         Serial.println("state 0");
//     case 0: // listening to button press
//         if (!digitalRead(BUTTONPIN1))
//         {
//             state = 0;
//             s = 1;
//             sendFlag = 1;
//         }
//         else if (!digitalRead(BUTTONPIN2))
//         {
//             state = 1;
//             s = 1;
//             sendFlag = 1;
//         }
//         else if (!digitalRead(BUTTONPIN3))
//         {
//             state = 2;
//             s = 1;
//             sendFlag = 1;
//         }
//         else if (!digitalRead(BUTTONPIN4))
//         {
//             s = 2;
//         }
//         break;
//     case 1: //  sending alarm state
//         Serial.println("state 1");
//         switch (state)
//         {
//         case 0:
//             strip.setPixelColor(0, strip.Color(255, 0, 0));
//             strip.show();
//             delay(500);
//             strip.setPixelColor(0, strip.Color(0, 0, 0));
//             strip.show();
//             delay(500);
//             break;
//         case 1:
//             strip.setPixelColor(1, strip.Color(0, 255, 0));
//             strip.show();
//             delay(500);
//             strip.setPixelColor(1, strip.Color(0, 0, 0));
//             strip.show();
//             delay(500);
//             break;
//         case 2:
//             strip.setPixelColor(2, strip.Color(0, 0, 255));
//             strip.show();
//             delay(500);
//             strip.setPixelColor(2, strip.Color(0, 0, 0));
//             strip.show();
//             delay(500);
//             break;
//         }

//         // Send data
//         if (sendFlag)
//         {
//             Serial.println("sending feedback");
//             Serial.println(state);
//             sendBuffer[0] = (char)state;
//             sendBuffer[1] = 'A';
//             ResponseStatus rs = e32ttl100.sendBroadcastFixedMessage(channels[channel_selected], String(sendBuffer));
//             Serial.println(rs.getResponseDescription());
//             Serial.println(rs.code); // 1 if Success
//             if (rs.code != 1)
//             {
//                 do
//                 {
//                     Serial1.println("Sending data waiting for success");
//                     ResponseStatus rs = e32ttl100.sendBroadcastFixedMessage(channels[channel_selected], sendBuffer);
//                     Serial.println(rs.getResponseDescription());
//                     Serial.println(rs.code); // 1 if Success
//                 } while (rs.code != 1);
//             }
//             Serial.println("ACK received");
//             sendFlag = 0;
//         }
//         break;

//     case 2: //  select network ID
//         Serial.println("state 2");
//         NETWORKID > 8 ? NETWORKID = 0 : NETWORKID++;
//         // radio.initialize(FREQUENCY, MYNODEID, NETWORKID);
//         // radio.setHighPower(); // Always use this for RFM69HCW
//         sevensegment(NETWORKID);
//         delay(500);
//         s = 0; // listen to button press once more
//         break;

//     case 3: // send response
//         Serial.println("state 3");
//         switch (state)
//         {
//         case 0:
//             strip.setPixelColor(0, strip.Color(255, 0, 0));
//             strip.show();
//             delay(500);
//             strip.setPixelColor(0, strip.Color(0, 0, 0));
//             strip.show();
//             delay(500);
//             break;
//         case 1:
//             strip.setPixelColor(1, strip.Color(0, 255, 0));
//             strip.show();
//             delay(500);
//             strip.setPixelColor(1, strip.Color(0, 0, 0));
//             strip.show();
//             delay(500);
//             break;
//         case 2:
//             strip.setPixelColor(2, strip.Color(0, 0, 255));
//             strip.show();
//             delay(500);
//             strip.setPixelColor(2, strip.Color(0, 0, 0));
//             strip.show();
//             delay(500);
//             break;
//         }

//         if (!digitalRead(BUTTONPIN1))
//         {
//             stateRef = 0;
//         }
//         else if (!digitalRead(BUTTONPIN2))
//         {
//             stateRef = 1;
//         }
//         else if (!digitalRead(BUTTONPIN3))
//         {
//             stateRef = 2;
//         }

//         if (stateRef == state && sendFlag)
//         {
//             Serial.println("send stop blinking command");
//             sendBuffer[0] = (char)state;
//             sendBuffer[1] = 'C';
//             ResponseStatus rs = e32ttl100.sendBroadcastFixedMessage(channels[channel_selected], sendBuffer);
//             Serial.println(rs.getResponseDescription());
//             Serial.println(rs.code); // 1 if Success
//             if (rs.code != 1)
//             {
//                 do
//                 {
//                     Serial1.println("Sending data waiting for success");
//                     ResponseStatus rs = e32ttl100.sendBroadcastFixedMessage(channels[channel_selected], sendBuffer);
//                     Serial.println(rs.getResponseDescription());
//                     Serial.println(rs.code); // 1 if Success
//                 } while (rs.code != 1);
//             }
//             Serial.println("ACK received");
//             s = 0;
//             stateRef = 10;
//             state = 10;
//             sendFlag = 0;
//         }
//         break;
//     }

//     // check if data is available
//     if (e32ttl100.available() > 1) // radio.receiveDone()) // Got one!
//     {
//         // Print out the information:
//         ResponseContainer rs = e32ttl100.receiveMessage();
//         // First of all get the data
//         String message = rs.data;

//         Serial.print("received from node ");
//         // Serial.print(radio.SENDERID, DEC);
//         Serial.print(", message [");
//         Serial.println(message);

//         // The actual message is contained in the DATA array,
//         // and is DATALEN bytes in size:

//         if (s == 1 && message.indexOf("C") > 0) // sending alarm state
//         {
//             if (message.indexOf(state) > 0)
//             {
//                 Serial.println("Clear alarm");
//                 state = 10;
//                 s = 0; // go back to listen to button press
//             }
//         }
//         else if (s == 0 && message.indexOf("A") > 0) // listening to button presses
//         {
//             if (message.indexOf("0") > 0 || message.indexOf("2") > 0 || message.indexOf("2") > 0) // incoming data is valid alarm
//             {
//                 Serial.print("State is now: ");
//                 if (message.indexOf("0") > 0)
//                     state = 0;
//                 else if (message.indexOf("1") > 0)
//                     state = 1;
//                 else if (message.indexOf("2") > 0)
//                     state = 2;

//                 Serial.println(state);
//                 s = 3;
//                 sendFlag = 1;
//             }
//         }
//     }
// }

// void sevensegment(uint8_t num)
// {
//     switch (num)
//     {
//     case 0:
//         digitalWrite(pinA, HIGH);
//         digitalWrite(pinB, HIGH);
//         digitalWrite(pinC, HIGH);
//         digitalWrite(pinD, HIGH);
//         digitalWrite(pinE, HIGH);
//         digitalWrite(pinF, HIGH);
//         digitalWrite(pinG, LOW);
//         break;
//     case 1:
//         digitalWrite(pinA, LOW);
//         digitalWrite(pinB, HIGH);
//         digitalWrite(pinC, HIGH);
//         digitalWrite(pinD, LOW);
//         digitalWrite(pinE, LOW);
//         digitalWrite(pinF, LOW);
//         digitalWrite(pinG, LOW);
//         break;
//     case 2:
//         digitalWrite(pinA, HIGH);
//         digitalWrite(pinB, HIGH);
//         digitalWrite(pinC, LOW);
//         digitalWrite(pinD, HIGH);
//         digitalWrite(pinE, HIGH);
//         digitalWrite(pinF, LOW);
//         digitalWrite(pinG, HIGH);
//         break;
//     case 3:
//         digitalWrite(pinA, HIGH);
//         digitalWrite(pinB, HIGH);
//         digitalWrite(pinC, HIGH);
//         digitalWrite(pinD, HIGH);
//         digitalWrite(pinE, LOW);
//         digitalWrite(pinF, LOW);
//         digitalWrite(pinG, HIGH);
//         break;
//     case 4:
//         digitalWrite(pinA, LOW);
//         digitalWrite(pinB, HIGH);
//         digitalWrite(pinC, HIGH);
//         digitalWrite(pinD, LOW);
//         digitalWrite(pinE, LOW);
//         digitalWrite(pinF, HIGH);
//         digitalWrite(pinG, HIGH);
//         break;
//     case 5:
//         digitalWrite(pinA, HIGH);
//         digitalWrite(pinB, LOW);
//         digitalWrite(pinC, HIGH);
//         digitalWrite(pinD, HIGH);
//         digitalWrite(pinE, LOW);
//         digitalWrite(pinF, HIGH);
//         digitalWrite(pinG, HIGH);
//         break;
//     case 6:
//         digitalWrite(pinA, HIGH);
//         digitalWrite(pinB, LOW);
//         digitalWrite(pinC, HIGH);
//         digitalWrite(pinD, HIGH);
//         digitalWrite(pinE, HIGH);
//         digitalWrite(pinF, HIGH);
//         digitalWrite(pinG, HIGH);
//         break;
//     case 7:
//         digitalWrite(pinA, HIGH);
//         digitalWrite(pinB, HIGH);
//         digitalWrite(pinC, HIGH);
//         digitalWrite(pinD, LOW);
//         digitalWrite(pinE, LOW);
//         digitalWrite(pinF, LOW);
//         digitalWrite(pinG, LOW);
//         break;
//     case 8:
//         digitalWrite(pinA, HIGH);
//         digitalWrite(pinB, HIGH);
//         digitalWrite(pinC, HIGH);
//         digitalWrite(pinD, HIGH);
//         digitalWrite(pinE, HIGH);
//         digitalWrite(pinF, HIGH);
//         digitalWrite(pinG, HIGH);
//         break;
//     case 9:
//         digitalWrite(pinA, HIGH);
//         digitalWrite(pinB, HIGH);
//         digitalWrite(pinC, HIGH);
//         digitalWrite(pinD, HIGH);
//         digitalWrite(pinE, LOW);
//         digitalWrite(pinF, HIGH);
//         digitalWrite(pinG, HIGH);
//         break;
//     }
// }

// void colorWipe(uint32_t color, int wait)
// {
// }

// void updateLoraParameters(int channel_selected)
// {

//     ResponseStructContainer c;
//     c = e32ttl100.getConfiguration();
//     Configuration configuration = *(Configuration *)c.data;
//     configuration.ADDL = 3;
//     configuration.ADDH = 0;
//     configuration.CHAN = channels[channel_selected];
//     configuration.OPTION.fixedTransmission = FT_TRANSPARENT_TRANSMISSION;
//     configuration.OPTION.wirelessWakeupTime = WAKE_UP_250;

//     configuration.OPTION.fec = FEC_1_ON;
//     configuration.OPTION.ioDriveMode = IO_D_MODE_PUSH_PULLS_PULL_UPS;
//     configuration.OPTION.transmissionPower = POWER_10;

//     configuration.SPED.airDataRate = AIR_DATA_RATE_010_24;
//     configuration.SPED.uartBaudRate = UART_BPS_9600;
//     configuration.SPED.uartParity = MODE_00_8N1;

//     e32ttl100.setConfiguration(configuration, WRITE_CFG_PWR_DWN_SAVE);
//     printParameters(configuration);
//     c.close();
// }

// void printParameters(struct Configuration configuration)
// {
//     Serial.println("----------------------------------------");

//     Serial.print(F("HEAD : "));
//     Serial.print(configuration.HEAD, BIN);
//     Serial.print(" ");
//     Serial.print(configuration.HEAD, DEC);
//     Serial.print(" ");
//     Serial.println(configuration.HEAD, HEX);
//     Serial.println(F(" "));
//     Serial.print(F("AddH : "));
//     Serial.println(configuration.ADDH, DEC);
//     Serial.print(F("AddL : "));
//     Serial.println(configuration.ADDL, DEC);
//     Serial.print(F("Chan : "));
//     Serial.print(configuration.CHAN, DEC);
//     Serial.print(" -> ");
//     Serial.println(configuration.getChannelDescription());
//     Serial.println(F(" "));
//     Serial.print(F("SpeedParityBit     : "));
//     Serial.print(configuration.SPED.uartParity, BIN);
//     Serial.print(" -> ");
//     Serial.println(configuration.SPED.getUARTParityDescription());
//     Serial.print(F("SpeedUARTDatte  : "));
//     Serial.print(configuration.SPED.uartBaudRate, BIN);
//     Serial.print(" -> ");
//     Serial.println(configuration.SPED.getUARTBaudRate());
//     Serial.print(F("SpeedAirDataRate   : "));
//     Serial.print(configuration.SPED.airDataRate, BIN);
//     Serial.print(" -> ");
//     Serial.println(configuration.SPED.getAirDataRate());

//     Serial.print(F("OptionTrans        : "));
//     Serial.print(configuration.OPTION.fixedTransmission, BIN);
//     Serial.print(" -> ");
//     Serial.println(configuration.OPTION.getFixedTransmissionDescription());
//     Serial.print(F("OptionPullup       : "));
//     Serial.print(configuration.OPTION.ioDriveMode, BIN);
//     Serial.print(" -> ");
//     Serial.println(configuration.OPTION.getIODroveModeDescription());
//     Serial.print(F("OptionWakeup       : "));
//     Serial.print(configuration.OPTION.wirelessWakeupTime, BIN);
//     Serial.print(" -> ");
//     Serial.println(configuration.OPTION.getWirelessWakeUPTimeDescription());
//     Serial.print(F("OptionFEC          : "));
//     Serial.print(configuration.OPTION.fec, BIN);
//     Serial.print(" -> ");
//     Serial.println(configuration.OPTION.getFECDescription());
//     Serial.print(F("OptionPower        : "));
//     Serial.print(configuration.OPTION.transmissionPower, BIN);
//     Serial.print(" -> ");
//     Serial.println(configuration.OPTION.getTransmissionPowerDescription());

//     Serial.println("----------------------------------------");
// }
