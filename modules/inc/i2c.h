
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
err_t i2c_send_start(i2c_peripheral_t* i2c_peripheral);
err_t i2c_send_stop(i2c_peripheral_t* i2c_peripheral);
err_t i2c_send_addr(i2c_peripheral_t* i2c_peripheral, uint8_t slave_address);
err_t i2c_send_byte(i2c_peripheral_t* i2c_peripheral, uint8_t slave_address, uint8_t byte_to_send);
err_t i2c_send_stream(i2c_peripheral_t* i2c_peripheral, uint8_t slave_address, uint8_t* tx_buffer, uint32_t tx_len);
uint8_t i2c_receive_byte(i2c_peripheral_t* i2c_peripheral, uint8_t slave_address);
err_t i2c_receive_stream(i2c_peripheral_t* i2c_peripheral, uint8_t slave_address, uint8_t* rx_buffer, uint32_t rx_len);

#endif // INC_I2C_H