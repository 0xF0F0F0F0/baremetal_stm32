#ifndef INC_WM8731_H
#define INC_WM8731_H

#include "i2c.h"
#include "errors.h"

err_t wm8731_init(i2c_peripheral_t* i2c_peripheral, uint8_t slave_address, uint8_t* cmd_buffer, uint32_t cmd_len);
err_t wm8731_reset(i2c_peripheral_t* i2c_peripheral, uint8_t slave_address, uint16_t value);

#endif // INC_WM8731_H