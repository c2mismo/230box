 /*
 * State testing, developer c2mismo 2019.
 * License GNU, see at the end.
 */

//           LIBRARY CONF

#include "Arduino.h"
#include <SPI.h>
#include "Leds.h"
#include "Voltmeter.h"
#include "Ammeter.h"
#include "mcp2515.h"

struct can_frame canMsgValue230_12;
struct can_frame canMsgState230_12;
struct can_frame canMsg12_230;
MCP2515 mcp2515(53);

//  Read canBus 12box Signals
bool signalLeft;
bool signalRight;
//  END read canBus 12box Signals

//  Send canBus 12box Values
byte byteVoltageLeft;
byte byteVoltageRight;
byte byteVoltageIn;
byte byteSlowAmper;
//  END send canBus 12box Values

//  Send canBus 12box States
bool stateAutomatic = false;
bool stateLeftIn = false;
bool stateLeftOut = false;
bool stateRightIn = false;
bool stateRightOut = false;
bool stateCHR = false;
bool stateHome = false;
bool stateInverter = false;
//  END send canBus 12box States

//         END LIBRARY CONF

//             PINS

const int signalOn = A0;
const int signalHome = 5;

const int voltmeterLeftPin = A9;
const int voltmeterRightPin = A10;
const int voltmeterInPin = A11;
const int ammeterPin = A8;

const int ledLeftIn = 40;
const int ledLeftOut = 41;
const int ledRightIn = 42;
const int ledRightOut = 43;
const int ledInverter = 44;
const int ledCHR = 45;
const int ledHome = 46;
const int ledAutomatic = 47;

Leds leds (ledLeftIn, ledLeftOut, ledRightIn, ledRightOut, ledInverter, ledCHR, ledHome, ledAutomatic);

const int releRightIn = A1;
const int releLeftIn = A2;
const int releRightOut = A3;
const int releLeftOut = A4;
const int releHome = A5;
const int releCHR = A7;
const int reles[7] = {releRightIn, releLeftIn, releRightOut, releLeftOut, releHome, releCHR};

//            END PINS

//           VARIABLES

int freq = 20;      // 50 Hz = 20 m/s; 60 Hz = 16.6667 m/s
float calibAmper = 20.6;
int intervalRead = 250;
float amperMax = 5;
Voltmeter voltmeterLeft (voltmeterLeftPin, freq);
Voltmeter voltmeterRight (voltmeterRightPin, freq);
Voltmeter voltmeterIn (voltmeterInPin, freq);
Ammeter ammeter (ammeterPin, freq, calibAmper, intervalRead, amperMax);

//         END VARIABLES

//       FUNCTIONS DECLARED

void msgValue (byte, byte, byte, byte);
void msgState (byte, byte, byte, byte, byte, byte, byte, byte);

//       END FUNCTIONS DECLARED

void setup(){
  while (!Serial);
  Serial.begin(115200);
  SPI.begin();

  mcp2515.reset();
  mcp2515.setBitrate (CAN_500KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();

  canMsgValue230_12.can_id = 0x036;
  canMsgValue230_12.can_dlc = 4;
  canMsgState230_12.can_id = 0x037;
  canMsgState230_12.can_dlc = 8;

  pinMode(signalOn, INPUT);
  pinMode(signalHome, INPUT_PULLUP);

  pinMode(releRightIn, OUTPUT);
  pinMode(releLeftIn, OUTPUT);
  pinMode(releRightOut, OUTPUT);
  pinMode(releLeftOut, OUTPUT);
  pinMode(releHome, OUTPUT);
  pinMode(releCHR, OUTPUT);

  //leds.blinkOn();
}

void loop(){
  digitalWrite(ledAutomatic, HIGH);
  digitalWrite(releLeftIn, HIGH);

  voltmeterLeft.get();
  float voltageLeft = voltmeterLeft.getVoltage();
  byteVoltageLeft = voltageLeft;

  voltmeterRight.get();
  float voltageRight = voltmeterRight.getVoltage();
  byteVoltageRight = voltageRight;

  voltmeterIn.get();
  float voltageIn = voltmeterIn.getVoltage();
  byteVoltageIn = voltageIn;

  ammeter.get();
  float slowAmper = ammeter.getAmperSlow();
  byteSlowAmper = slowAmper;
  stateInverter = true;

  // Rear data from 12box
  if (mcp2515.readMessage(&canMsg12_230) == MCP2515::ERROR_OK)
  {
    signalLeft = canMsg12_230.data[0];
    signalRight = canMsg12_230.data[1];
  }
  // END rear data from 12box

  msgValue(byteVoltageLeft, byteVoltageRight, byteVoltageIn, byteSlowAmper);
  msgState(stateAutomatic, stateLeftIn, stateLeftOut, stateRightIn, stateRightOut, stateCHR, stateHome, stateInverter);
  //delay(1200);
}

//           FUNCTIONS

void msgValue (byte valueLeft, byte valueRight, byte valueIn, byte valueAmper)
{
  if (valueLeft >= 255) {
    canMsgValue230_12.data[0] = 255;
  } else {
    canMsgValue230_12.data[0] = valueLeft;
  }

  if (valueRight >= 255) {
    canMsgValue230_12.data[1] = 255;
  } else {
    canMsgValue230_12.data[1] = valueRight;
  }

  if (valueIn >= 255) {
    canMsgValue230_12.data[2] = 255;
  } else {
    canMsgValue230_12.data[2] = valueIn;
  }

  canMsgValue230_12.data[3] = valueAmper; // Reserved for Ampermeter

  mcp2515.sendMessage(&canMsgValue230_12);
}

void msgState (byte stateAutomatic, byte stateLeftIn, byte stateLeftOut, byte stateRightIn, byte stateRightOut, byte stateCHR, byte stateHome, byte stateInverter)
{
  canMsgState230_12.data[0] = stateAutomatic;
  canMsgState230_12.data[1] = stateLeftIn;
  canMsgState230_12.data[2] = stateLeftOut;
  canMsgState230_12.data[3] = stateRightIn;
  canMsgState230_12.data[4] = stateRightOut;
  canMsgState230_12.data[5] = stateCHR;
  canMsgState230_12.data[6] = stateHome;
  canMsgState230_12.data[7] = stateInverter;

  mcp2515.sendMessage(&canMsgState230_12);
}

//         END FUNCTIONS

/*
  License:

    Copyright (C) 2019  c2mismo.

    This file is part of 230box.

    230box is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This 230box is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this 230box, see COPYING.  If not, see <https://www.gnu.org/licenses/>.

    You can download a full copy of 230box at <https://github.com/c2mismo>.
 */
