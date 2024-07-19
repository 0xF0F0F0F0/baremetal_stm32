
#ifndef INC_I2C_H
#define INC_I2C_H

#include "stm32f4xx.h"
#include "core_clock.h"
#include "errors.h"
#include <stdbool.h>

typedef struct {
	I2C_TypeDef* I2Cx;
	bool is_master;
} i2c_peripheral_t;

err_t i2c_peripheral_init(i2c_peripheral_t* i2c_peripheral);
err_t i2c_send(i2c_peripheral_t* i2c_peripheral, uint8_t slave_address, uint8_t* tx_buffer, uint32_t tx_len);
err_t i2c_receive(i2c_peripheral_t* i2c_peripheral, uint8_t slave_address, uint8_t* rx_buffer, uint32_t rx_len);

#endif // INC_I2C_H