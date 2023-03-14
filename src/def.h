#ifndef DEF_H
#define DEF_H

#include "Arduino.h"
#include <Adafruit_NeoPixel.h>
#include "LoRa_E32.h"

// Addressable leds
#define LEDPIN PA5
#define LEDCOUNT 3

// leds
#define LED_GREEN PB8
#define LED_YELLOW PB7
#define LED_RED PB6

// Buttons
#define BUTTON_CHANNEL PA1 // edit channel number
#define BUTTON_GREEN PA2   // state = 1
#define BUTTON_YELLOW PA3  // state = 2
#define BUTTON_RED PA4     // state = 3

// battery voltage level
#define BATTERY_VOLTAGE_PIN PA8
#define BATTERY_STAT1 PA6
#define BATTERY_STAT2 PA7
#define BATTERY_SUPERVISOR_PIN PA0
#define BATTERY_SUPERVISOR_CLR PB1

#define BATTERY_VOLTAGE_FULL (3.8 * (3.3 / 4.2) * 4095)
#define BATTERY_VOLTAGE_OKAY (3.3 * (3.3 / 4.2) * 4095)
#define BATTERY_VOLTAGE_LOW (3.0 * (3.3 / 4.2) * 4095)
#define BATTERY_VOLTAGE_LOW (3.0 * (3.3 / 4.2) * 4095)

// seven-segment display
#define pinA PB9
#define pinB PB10
#define pinC PB11
#define pinD PB12
#define pinE PB13
#define pinF PB14
#define pinG PB15

// Lora frequency
#define FREQUENCY_915

// Lora pins
#define lora_TX PA9  // ADD INTERNAL PULLUP
#define lora_RX PA10 // ADD INTERNAL PULLUP
#define lora_AUX PB5 // KEEP FLOAING/ HIGH IMPEDANCE INPUT WITH NO CONNECTION TO GND OR PWR
#define lora_M1 PB3  // PULL TO GND FOR NORMAL OPERATION OF BYTE
#define lora_M0 PB4  // PULL TO GND FOR NORMAL OPERATION OF BYTE

#define NEOPIXEL_FLASH_ON_PERIOD_MS 1000  // turn the addrressable led ON for 1 second
#define NEOPIXEL_FLASH_OFF_PERIOD_MS 3000 // turn the addrressable led OFF for 3 seconds

// ---------- initialization
void initializePins();

// ---------- variables
extern int state;
extern int selectedChannel;
extern int channels[];
extern int lastExecutionMillis;

// ---------- button functions
void checkForButtonPress();

// ---------- leds variables/functions
void setupNeopixels();
void flashNeopixel(int pixel, int r, int g, int b);
void flashStateLED();

// ---------- lora variables/functions
void setupLora();
void changeLoraChannel();
void sendLoraData(int state);
void checkIncomingLoraData();

// ---------- seven-segment variables/functions
void updateSevenSegmentDisplay(int number);

// power monitoring
void checkBatteryVoltage();

#endif