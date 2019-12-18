/*
 * Example for AnalogWritePlus
 * 
 * Para calibrar:
 * Primero fanMin 0 & fanMax = top
 * los valores de calib entre 0 & top.
 * valor = 1
 * Aumenta calibMin hasta un valor aceptable
 * Disminuye calibMax hasta un valor aceptable
 * 
 * los valores resultantes los indicas como fanMIn & fan Max
 * 
 * Developer c2mismo 2019.
 * License GNU, see at the end.
 */


#include "Arduino.h"
#include "AnalogWritePlus2.h"

int fanMin = 30;
int fanMax = 230;

AnalogWritePlus2 Plus9 (9, fanMin, fanMax);

byte valor = 0; // 0 to 100%
int top = 230; // Value frecuency MHz
int valorMin = 0;
int valorMax = 0;
int option;
int pwm;

void setup()
{
  Serial.begin(9600);
  Plus9.begin(top); // Valor maximo PWM
  Serial.print("Valor = ");
  Serial.println(valor);
}

void loop()
{
  // Para ir calibrando
  // Descomentar valorMin, valorMax o write de uno en uno.
  
  // Descomentar para valorMin, buscar valores mínimos
  // Una vez identificado indicarlo a fanMin
  
  //Plus9.calibMin(valorMin); // valor entre 0 & Valor maximo PWM
  
  // Descomentar para valorMax, buscar valores máximos
  // Una vez identificado indicarlo a fanMax
  
  //Plus9.calibMax(valorMax); // valor entre 0 & Valor maximo PWM
  
  // Descomentar para write, comprobar calibración
  
  Plus9.write(valor); // valor entre 0% & 100% equibale a 0 & Valor maximo PWM


  if (Serial.available()>0){
    option=Serial.read();

    // Descomentar para valorMin
    /*
    if(option=='8') {
      if (valorMin < top) valorMin += 1;
      if (valorMin > top) valorMin = top;
      Serial.print("valorMin = ");
      Serial.println(valorMin);
    }
    if(option=='2') {
      if (valorMin > 0) valorMin -= 1;
      if (valorMin < 0) valorMin = 0;
      Serial.print("valorMin = ");
      Serial.println(valorMin);
    }
    if(option=='9') {
      if (valorMin >= top-10) valorMin = top;
      if (valorMin < top-10) valorMin += 10;
      Serial.print("valorMin = ");
      Serial.println(valorMin);
    }
    if(option=='3') {
      if (valorMin <= 10) valorMin = 0;
      if (valorMin > 10) valorMin -= 10;
      Serial.print("valorMin = ");
      Serial.println(valorMin);
    }
    if(option=='7') {
      valorMin = top;
      Serial.print("valorMin = ");
      Serial.println(valorMin);
    }
    if(option=='1') {
      valorMin = 0;
      Serial.print("valorMin = ");
      Serial.println(valorMin);
    } */

    // Descomentar para calMax
    /*
    if(option=='8') {
      if (valorMax < top) valorMax += 1;
      if (valorMax > top) valorMax = top;
      Serial.print("valorMax = ");
      Serial.println(valorMax);
    }
    if(option=='2') {
      if (valorMax > 0) valorMax -= 1;
      if (valorMax < 0) valorMax = 0;
      Serial.print("valorMax = ");
      Serial.println(valorMax);
    }
    if(option=='9') {
      if (valorMax >= top-10) valor = top;
      if (valorMax < top-10) valorMax += 10;
      Serial.print("valorMax = ");
      Serial.println(valorMax);
    }
    if(option=='3') {
      if (valorMax <= 10) valorMax = 0;
      if (valorMax > 10) valorMax -= 10;
      Serial.print("valorMax = ");
      Serial.println(valorMax);
    }
    if(option=='7') {
      valorMax = top;
      Serial.print("valorMax = ");
      Serial.println(valorMax);
    }
    if(option=='1') {
      valorMax = 0;
      Serial.print("valorMax = ");
      Serial.println(valorMax);
    } */

        // Descomentar para write
    //*
    if(option=='8') {
      if (valor < 100) valor += 1;
      if (valor > 100) valor=100;
      Serial.print("Valor = ");
      Serial.print(valor);
      pwm=map(valor,1,100,fanMin,fanMax);
      Serial.print("    PWM = ");
      Serial.println(pwm);
    }
    if(option=='2') {
      if (valor > 0) valor -= 1;
      if (valor < 0) valor = 0;
      Serial.print("Valor = ");
      Serial.print(valor);
      pwm=map(valor,1,100,fanMin,fanMax);
      if (pwm < 0) pwm = 0;
      Serial.print("    PWM = ");
      Serial.print(pwm);
      if (valor < 1) Serial.print("    Valor real PWM = 0");
      Serial.println();
    }
    if(option=='9') {
      if (valor >= 90) valor = 100;
      if (valor < 90) valor += 10;
      Serial.print("Valor = ");
      Serial.print(valor);
      pwm=map(valor,1,100,fanMin,fanMax);
      Serial.print("    PWM = ");
      Serial.println(pwm);
    }
    if(option=='3') {
      if (valor <= 10) valor = 0;
      if (valor > 10) valor -= 10;
      Serial.print("Valor = ");
      Serial.print(valor);
      pwm=map(valor,1,100,fanMin,fanMax);
      if (pwm < 0) pwm = 0;
      Serial.print("    PWM = ");
      Serial.print(pwm);
      if (valor < 1) Serial.print("    Valor real PWM = 0");
      Serial.println();
    }
    if(option=='7') {
      valor = 100;
      Serial.print("Valor = ");
      Serial.print(valor);
      pwm=map(valor,1,100,fanMin,fanMax);
      Serial.print("    PWM = ");
      Serial.println(pwm);
    }
    if(option=='1') {
      valor = 0;
      Serial.print("Valor = ");
      Serial.print(valor);
      pwm=map(valor,1,100,fanMin,fanMax);
      if (pwm < 0) pwm = 0;
      Serial.print("    PWM = ");
      Serial.print(pwm);
      if (valor < 1) Serial.print("    Valor real PWM = 0");
      Serial.println();
    } //*/
    
  }
}

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
