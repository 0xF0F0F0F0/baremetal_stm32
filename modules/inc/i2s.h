#ifndef INC_I2S_H
#define INC_I2S_H

#include "stm32f4xx.h"
#include "errors.h"
#include "core_clock.h"

//err_t i2s_init(SPI_TypeDef* i2s_peripheral, uint16_t* tx_buffer_A, uint16_t* tx_buffer_B, uint16_t* rx_buffer_A, uint16_t* rx_buffer_B);
err_t i2s_init(SPI_TypeDef* i2s_peripheral, int16_t (*tx_buffer)[4], int16_t (*rx_buffer)[4]);

#endif // INC_I2S_H

