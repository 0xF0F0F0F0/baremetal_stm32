#ifndef INC_ERRORS_H
#define INC_ERRORS_H

typedef enum {
	EOK = 0,
	ERR1,
	ERR2,
	ERR3,
	ERR_I2C_ADDR_NACK,
	ERR_I2C_DATA_NACK
} err_t;

#endif // INC_ERRORS_H