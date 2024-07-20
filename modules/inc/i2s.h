#ifndef INC_I2S_H
#define INC_I2S_H

#include "stm32f4xx.h"
#include "errors.h"
#include "core_clock.h"


err_t i2s_init(SPI_TypeDef* i2s_peripheral);

#endif // INC_I2S_H

