#pragma once

/*
    Dynamixel2.h

    For control of Dynamixel Servos using Protocol 2.0

    Part of Grbl_ESP32

    2020 -	Bart Dring

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

#include "Servo.h"
#include "../Pin.h"

#include "../Uart.h"

#include <cstdint>

namespace Motors {
    class Dynamixel2 : public Servo {
    protected:
        void config_message() override;

        void set_location();

        uint8_t _id;
        char    _dxl_tx_message[50];  // outgoing to dynamixel
        uint8_t _dxl_rx_message[50];  // received from dynamixel

        bool     test();
        uint16_t dxl_get_response(uint16_t length);
        uint32_t dxl_read_position();
        void     dxl_read(uint16_t address, uint16_t data_len);
        void     dxl_write(uint16_t address, uint8_t paramCount, ...);
        void     dxl_goal_position(int32_t position);  // set one motor
        void     set_operating_mode(uint8_t mode);
        void     LED_on(bool on);

        static void     dxl_finish_message(uint8_t id, char* msg, uint16_t msg_len);
        static uint16_t dxl_update_crc(uint16_t crc_accum, char* data_blk_ptr, uint8_t data_blk_size);
        void            dxl_bulk_goal_position();

        float _homing_position;

        float _dxl_count_min;
        float _dxl_count_max;

        int           _axis_index;
        Setting<bool> _invert_direction = false;

        Uart* _uart = nullptr;

        static bool _uart_started;

        static const int DXL_RESPONSE_WAIT_TICKS = 20;  // how long to wait for a response

        // protocol 2 byte positions
        static const int DXL_MSG_HDR1  = 0;
        static const int DXL_MSG_HDR2  = 1;
        static const int DXL_MSG_HDR3  = 2;
        static const int DXL_MSG_RSRV  = 3;  // reserved byte
        static const int DXL_MSG_ID    = 4;
        static const int DXL_MSG_LEN_L = 5;
        static const int DXL_MSG_LEN_H = 6;
        static const int DXL_MSG_INSTR = 7;
        static const int DXL_MSG_START = 8;

        static const int DXL_BROADCAST_ID = 0xFE;

        // protocol 2 instruction numbers
        static const int  DXL_INSTR_PING = 0x01;
        static const int  PING_RSP_LEN   = 14;
        static const char DXL_READ       = char(0x02);
        static const char DXL_WRITE      = char(0x03);
        static const char DXL_SYNC_WRITE = char(0x83);

        // protocol 2 register locations
        static const int DXL_OPERATING_MODE   = 11;
        static const int DXL_ADDR_TORQUE_EN   = 64;
        static const int DXL_ADDR_LED_ON      = 65;
        static const int DXL_GOAL_POSITION    = 116;  // 0x74
        static const int DXL_PRESENT_POSITION = 132;  // 0x84

        // control modes
        static const int DXL_CONTROL_MODE_POSITION = 3;

        Setting<int> _countMin = 1024;
        Setting<int> _countMax = 3072;

        Setting<int> _dynamixelFullTimeMove = 1000;  // time in milliseconds to do a full DYNAMIXEL_FULL_MOVE_TIME

        bool _disabled;
        bool _has_errors;

    public:
        Dynamixel2() : _id(255), _disabled(true), _has_errors(true) {}

        // Overrides for inherited methods
        void init() override;
        void read_settings() override;
        bool set_homing_mode(bool isHoming) override;
        void set_disable(bool disable) override;
        void update() override;

        static uint8_t ids[MAX_N_AXIS][2];

        // Configuration handlers:
        void validate() const override {
            Assert(_uart != nullptr, "Dynamixel: Missing UART configuration");
            Assert(!_uart->_rts_pin.undefined(), "Dynamixel: UART RTS pin must be configured.");
            Assert(_id != 255, "Dynamixel: ID must be configured.");
        }

        void group(Configuration::HandlerBase& handler) override {
            handler.item("invert_direction", _invert_direction);

            handler.item("count_min", _countMin);
            handler.item("count_max", _countMax);
            handler.item("full_time_move", _dynamixelFullTimeMove);
            handler.section("uart", _uart);

            Setting<int> id = _id;
            handler.item("id", id);
            _id = id;
        }

        // Name of the configurable. Must match the name registered in the cpp file.
        const char* name() const override { return "dynamixel2"; }
    };
}
