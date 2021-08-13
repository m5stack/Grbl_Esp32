#pragma once

#include "Wire.h"

class BoardCtrl {

private:
    uint8_t I2CWriteRegByte(uint8_t slave_addr, uint8_t reg, uint8_t data) {
        wire_i2c->beginTransmission(slave_addr);
        wire_i2c->write(reg);
        wire_i2c->write(data);
        return wire_i2c->endTransmission();
    }

    uint8_t I2CReadRegByte(uint8_t slave_addr, uint8_t reg, uint8_t* data) {
        uint8_t result;
        wire_i2c->beginTransmission(slave_addr);
        wire_i2c->write(reg);
        result = wire_i2c->endTransmission();
        if (result != I2C_ERROR_OK) {
            return result;
        }
        if (wire_i2c->requestFrom((int)slave_addr, 1) == 0) {
            return I2C_ERROR_BUS;
        }
        *data = wire_i2c->read();
        return I2C_ERROR_OK;
    }

public:
    typedef enum {
        kMicrosteps1 = 0x00,
        kMicrosteps2 = 0x04,
        kMicrosteps4 = 0x02,
        kMicrosteps8 = 0x06,
        kMicrosteps16 = 0x01,
        kMicrosteps32 = 0x07,
    } MicrostepResolution_t;

    uint8_t _slave_addr;
    uint8_t ext_io_status[4];
    TwoWire* wire_i2c;

public:
    bool init(TwoWire& wire_in = Wire, uint8_t slave_addr = 0x27) {
        wire_i2c = &wire_in;
        _slave_addr = slave_addr;

        // IO 0 ~ 3 input, 4 ~ 7 out_put;
        return I2CWriteRegByte(_slave_addr, 0x03, 0x0f) == I2C_ERROR_OK;
    }

    void setMicrostepResolution(MicrostepResolution_t micro_step) {
        uint8_t reg_data = 0x00;
        I2CReadRegByte(_slave_addr, 0x01, &reg_data);
        reg_data &= 0x1f;
        reg_data |= micro_step << 5;
        I2CWriteRegByte(_slave_addr, 0x01, reg_data);
    }

    void enableMotor(uint8_t en) {
        uint8_t reg_data = 0x00;
        I2CReadRegByte(_slave_addr, 0x01, &reg_data);
        reg_data &= 0xef;
        if (en == 0) {
            reg_data |= 0x10;
        }
        I2CWriteRegByte(_slave_addr, 0x01, reg_data);
    }

    void getExtIOStatus(uint8_t* status = NULL) {
        uint8_t io_status = 0x00;
        if (I2CReadRegByte(_slave_addr, 0x00, &io_status) != I2C_ERROR_OK) {
            return ;
        }

        for (uint8_t i = 0; i < 4; i++) {
            ext_io_status[i] = (io_status & (0x01 << i)) ? 1 : 0;
        }

        if (status != NULL) {
            *status = io_status;
        }
    }
};

void userBoardInit();
