#include "i2c.h"

/**
 * I2C2: SCL-PB10, SDA-PB11, Freq:100k
 * Note: SCL SDA lines must have exteral pull-ups
 */

static void i2c_send_start(i2c_peripheral_t* i2c_peripheral)
{
	i2c_peripheral->I2Cx->CR1 |= I2C_CR1_START;
}

static void i2c_send_stop(i2c_peripheral_t* i2c_peripheral)
{
	i2c_peripheral->I2Cx->CR1 |= I2C_CR1_STOP;
}

err_t i2c_peripheral_init(i2c_peripheral_t* i2c_peripheral)
{
	if (I2C2 == (i2c_peripheral->I2Cx)) {
		// Enable clocks
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
		RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;

		// Reset peripheral
		RCC->APB1RSTR |= RCC_APB1RSTR_I2C2RST;
		RCC->APB1RSTR &= ~(RCC_APB1RSTR_I2C2RST);

		// Set GPIOB alt function, open drain, high speed
		GPIOB->MODER |= (GPIO_MODER_MODER10_1 | GPIO_MODER_MODER11_1);
		GPIOB->OTYPER |= (GPIO_OTYPER_OT_10 | GPIO_OTYPER_OT_11);
		GPIOB->OSPEEDR |= (GPIO_OSPEEDER_OSPEEDR10 | GPIO_OSPEEDER_OSPEEDR11);
		GPIOB->AFR[1] |= ((4 << 8) | (4 << 12)); // PB10, PB11 - AF4
	}

	// SW reset i2c
	i2c_peripheral->I2Cx->CR1 |= I2C_CR1_SWRST;
	i2c_peripheral->I2Cx->CR1 &= ~(I2C_CR1_SWRST);

	// Set i2c peripheral input clock in MHz
	i2c_peripheral->I2Cx->CR2 |= (I2C_CR2_FREQ & (uint16_t)(APB1_CLOCK_SPEED/1000000));

	// Set CCR register for 100kHz SCL line (5us on + 5us off)
	// CCR = 5us * 45MHz (as per datasheet)
	i2c_peripheral->I2Cx->CCR |= (I2C_CCR_CCR & (uint16_t)225);
	// TRISE = (1000ns * 45MHz) + 1 (as per datasheet)
	i2c_peripheral->I2Cx->TRISE |= (I2C_TRISE_TRISE & (uint8_t)46);

	// Enable the peripheral
	i2c_peripheral->I2Cx->CR1 |= I2C_CR1_PE;

	return EOK;
}

err_t i2c_send(i2c_peripheral_t* i2c_peripheral, uint8_t slave_address, uint8_t* tx_buffer, uint32_t tx_len)
{
	// This is specific to the WM8731 audio codec.
	// Every register write needs its own start and stop condtition.
	// The order should be: START->ADDR(W)->REGADDR->REGVALUE->STOP

	slave_address = (slave_address << 1);	// Slave address + Write

	// Send all register write commands in tx_buffer
	while (0 != tx_len) {

		// Send START condition
		i2c_send_start(i2c_peripheral);
		// Wait until START is generated
		while (!(i2c_peripheral->I2Cx->SR1 & I2C_SR1_SB));

		// Send 7-bit slave address + Read(1)/Write(0) bit
		i2c_peripheral->I2Cx->DR = slave_address;
		// Wait until Address has been sent and acknowledged
		while (!(i2c_peripheral->I2Cx->SR1 & I2C_SR1_ADDR)) {
			if (i2c_peripheral->I2Cx->SR1 & I2C_SR1_AF) {
				return ERR_I2C_ADDR_NACK;
			}
		}

		// Clear ADDR bit by reading SR1 followed by SR2
		i2c_peripheral->I2Cx->SR1 |=  i2c_peripheral->I2Cx->SR1;
		i2c_peripheral->I2Cx->SR2 |=  i2c_peripheral->I2Cx->SR2;

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

err_t i2c_receive(i2c_peripheral_t* i2c_peripheral, uint8_t slave_address, uint8_t* rx_buffer, uint32_t rx_len)
{

}