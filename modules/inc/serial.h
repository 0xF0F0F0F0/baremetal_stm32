#ifndef INC_SERIAL_H
#define INC_SERIAL_H

#include "stm32f4xx.h"
#include "errors.h"

#define BRR_MANTISSA_POS 4
#define BRR_FRACTION_POS 0

typedef enum {
	BAUD_9600,
	BAUD_115200
} baud_t;

err_t serial_init(baud_t baud_rate);
err_t serial_read_byte();
err_t serial_write_byte();

#endif // INC_SERIAL_H
