/*
 * AnalogWritePlus frecuency control for PWM optocoupled.
 * timer == Timer/counter by Atmel 
 *          For UNO we will use Timer 1 (not is possible with Servo, Toner, etc...)
 *          Pins 9 & 10.
 *          
 * fanMin and fanMax for calibrate fan.
 * 
 * Need use to begin and config frecuency
 * TOP = 400; 19.906 MHz; PWM fron 0 to 400
 * TOP = 320; 24.883 MHz
 * TOP = 200; 39.813 MHz
 * TOP = 100; 79.626 MHz
 * 
 * fanMin & fanMax for calibration use the valors of TOP.
 * 
 * pin = only fron his timer
 * 
 * value = percentage (0~100%)
 * 
 * State testing, developer c2mismo 2019.
 * License GNU, see at the end.
 */
#ifndef AnalogWritePlus2_h
#define AnalogWritePlus2_h

#include "Arduino.h"

class AnalogWritePlus2
{
	public:
			AnalogWritePlus2(const byte timer, int fanMin, int fanMax);
      void begin(int top);
			void calibMin(int calMin);
      void calibMax(int calMax);
      void write(byte value);
			
	private:
      byte _timer;
      int _fanMin;
      int _fanMax;
      int _top;
      int _calMin;
      int _calMax;
			byte _value;
			
};

#endif

/*
  License:

    Copyright (C) 2019  c2mismo.

    This file is part of AnalogWritePlus.

    AnalogWritePlus is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This AnalogWritePlus is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this AnalogWritePlus, see COPYING.  If not, see <https://www.gnu.org/licenses/>.

    You can download a full copy of AnalogWritePlus at <https://github.com/c2mismo>.
 */
