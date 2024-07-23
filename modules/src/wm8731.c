#include "wm8731.h"

err_t wm8731_init(i2c_peripheral_t* i2c_peripheral, uint8_t slave_address, uint8_t* tx_buffer, uint32_t tx_len)
{
	// This is specific to the WM8731 audio codec.
	// Every register write needs its own start and stop condtition.
	// The order should be: START->ADDR(W)->REGADDR->REGVALUE->STOP

	// Send all register write commands in tx_buffer
	while (0 != tx_len) {

		// Send START condition
		i2c_send_start(i2c_peripheral);

		// Send ADDR
		i2c_send_addr(i2c_peripheral, slave_address);


		// Send register address followed by register value from cmd_list
		for (uint8_t i = 0; i < 2; i++) {
			// Wait until the peripheral is ready to send (TXE flag = true)
			while(!(i2c_peripheral->I2Cx->SR1 & I2C_SR1_TXE)) {
				if (i2c_peripheral->I2Cx->SR1 & I2C_SR1_AF) {
					return ERR_I2C_DATA_NACK;
				}
			}

			// Put a byte from the tx_buffer into i2c data register
			i2c_peripheral->I2Cx->DR = *tx_buffer;
			*tx_buffer++;
			tx_len--;
		}

		// Wait for TXE=1 and BTF=1 (last byte transmited), Send STOP condition
		while (!(i2c_peripheral->I2Cx->SR1 & I2C_SR1_TXE));
		while (!(i2c_peripheral->I2Cx->SR1 & I2C_SR1_BTF));
		i2c_send_stop(i2c_peripheral);
	}

	return EOK;
}

err_t wm8731_reset(i2c_peripheral_t* i2c_peripheral, uint8_t slave_address, uint16_t value)
{
	// Send START condition
	i2c_send_start(i2c_peripheral);

	// Send ADDR
	i2c_send_addr(i2c_peripheral, slave_address);

	while(!(i2c_peripheral->I2Cx->SR1 & I2C_SR1_TXE)) {
		if (i2c_peripheral->I2Cx->SR1 & I2C_SR1_AF) {
			return ERR_I2C_DATA_NACK;
		}
	}

	i2c_peripheral->I2Cx->DR = 0b00010010; // Address of active reg in wm8731

	while(!(i2c_peripheral->I2Cx->SR1 & I2C_SR1_TXE)) {
		if (i2c_peripheral->I2Cx->SR1 & I2C_SR1_AF) {
			return ERR_I2C_DATA_NACK;
		}
	}

	i2c_peripheral->I2Cx->DR = value;

	// Wait for TXE=1 and BTF=1 (last byte transmited), Send STOP condition
	while (!(i2c_peripheral->I2Cx->SR1 & I2C_SR1_TXE));
	while (!(i2c_peripheral->I2Cx->SR1 & I2C_SR1_BTF));
	i2c_send_stop(i2c_peripheral);

	return EOK;
}