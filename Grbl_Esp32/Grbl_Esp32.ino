/*
  Grbl_ESP32.ino - Header for system level commands and real-time processes
  Part of Grbl
  Copyright (c) 2014-2016 Sungeun K. Jeon for Gnea Research LLC

	2018 -	Bart Dring This file was modified for use on the ESP32
					CPU. Do not use this with Grbl for atMega328P

  Grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "src/Grbl.h"
#include "src/UserBoard.h"
#include "Wire.h"
#include "M5Stack.h"

extern void userBoardInit(); 

void setup() {
    M5.begin(true, false, false, false);
    M5.Lcd.clear(TFT_BLACK);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setTextColor(TFT_GREEN);
    M5.Lcd.setTextDatum(MC_DATUM);
    M5.Lcd.drawString("GRBL", 160, 120, 4);
    grbl_init();
    userBoardInit();
}

void loop() {
    run_once();
}
