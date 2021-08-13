#pragma once
// clang-format off

/*
    3axis_v4.h
    Part of Grbl_ESP32

    Pin assignments for the ESP32 Development Controller, v4.1 and later.
    https://github.com/bdring/Grbl_ESP32_Development_Controller
    https://www.tindie.com/products/33366583/grbl_esp32-cnc-development-board-v35/

    2018    - Bart Dring
    2020    - Mitch Bradley

    Grbl_ESP32 is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Grbl is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Grbl_ESP32.  If not, see <http://www.gnu.org/licenses/>.
*/

#define MACHINE_NAME            "M5STACK Step Module"

#define CONNECT_TO_SSID  "cam"
#define SSID_PASSWORD  "88888888"

#define USE_RMT_STEPS
#define ENABLE_SOFTWARE_DEBOUNCE
#define USE_EXT_IO_PIN_LIMIT

#define EXT_IO_0 EXT_IN_PIN_BASE
#define EXT_IO_1 (EXT_IN_PIN_BASE + 1)
#define EXT_IO_2 (EXT_IN_PIN_BASE + 2)
#define EXT_IO_3 (EXT_IN_PIN_BASE + 3)

#define X_STEP_PIN              GPIO_NUM_16
#define X_DIRECTION_PIN         GPIO_NUM_17
#define Y_STEP_PIN              GPIO_NUM_12
#define Y_DIRECTION_PIN         GPIO_NUM_13
#define Z_STEP_PIN              GPIO_NUM_15
#define Z_DIRECTION_PIN         GPIO_NUM_0

#define X_LIMIT_PIN             EXT_IO_0
#define Y_LIMIT_PIN             EXT_IO_1
#define Z_LIMIT_PIN             EXT_IO_2

#define GRBL_SPI_FREQ 40000000
#define GRBL_SPI_SS 4
#define GRBL_SPI_MOSI 23
#define GRBL_SPI_MISO 19
#define GRBL_SPI_SCK 18

// OK to comment out to use pin for other features
// #define STEPPERS_DISABLE_PIN    GPIO_NUM_13

#define SPINDLE_TYPE    SpindleType::NONE
// #define SPINDLE_TYPE            SpindleType::PWM
// #define SPINDLE_OUTPUT_PIN      GPIO_NUM_2   // labeled SpinPWM
// #define SPINDLE_ENABLE_PIN      GPIO_NUM_22  // labeled SpinEnbl

// #define COOLANT_MIST_PIN        GPIO_NUM_21  // labeled Mist
// #define COOLANT_FLOOD_PIN       GPIO_NUM_25  // labeled Flood
// #define PROBE_PIN               GPIO_NUM_32  // labeled Probe

/*
#define CONTROL_SAFETY_DOOR_PIN GPIO_NUM_35  // labeled Door,  needs external pullup
#define CONTROL_RESET_PIN       GPIO_NUM_34  // labeled Reset, needs external pullup
#define CONTROL_FEED_HOLD_PIN   GPIO_NUM_36  // labeled Hold,  needs external pullup
#define CONTROL_CYCLE_START_PIN GPIO_NUM_39  // labeled Start, needs external pullup
*/

