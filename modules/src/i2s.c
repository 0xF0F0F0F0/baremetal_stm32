#include "i2s.h"

/**
 * SPI3 - I2S3 (TX/DAC data), I2S3ext (RX/ADC data) full-duplex
 *
 * LRCK - PA4 - altfunc 6
 * SCK - PB3 - altfunc 6
 * SD - (SO on board, DAC data) - PB5 - altfunc 6
 * SD_ext - (SI on board, ADC data) - PB4 - altfunc 7
 */

err_t i2s_init(SPI_TypeDef* i2s_peripheral)
{
	if (SPI3 == i2s_peripheral) {
		// Enable clocks
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
		RCC->APB1ENR |= RCC_APB1ENR_SPI3EN;

		// Reset peripheral
		RCC->APB1RSTR |= RCC_APB1RSTR_SPI3RST;
		RCC->APB1RSTR &= ~(RCC_APB1RSTR_SPI3RST);

		// Set GPIOA alt function, high speed
		GPIOA->MODER |= GPIO_MODER_MODER4_1;
		GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR4;
		GPIOA->AFR[0] |= (6 << 16); // PA4 - AF6

		// Set GPIOB alt function, high speed
		GPIOB->MODER |= (GPIO_MODER_MODER3_1 | GPIO_MODER_MODER4_1 | GPIO_MODER_MODER5_1);
		GPIOB->OSPEEDR |= (GPIO_OSPEEDER_OSPEEDR3 | GPIO_OSPEEDER_OSPEEDR4 | GPIO_OSPEEDER_OSPEEDR5);
		GPIOB->AFR[0] |= ((6 << 12) | (6 << 20) | (7 << 16)); // PB3, PB5 - AF6, PB4 - AF7
	}

	// Enable I2S mode
	i2s_peripheral->I2SCFGR |= SPI_I2SCFGR_I2SMOD;
	// I2SCFGR on reset: slave tx, i2s philips std. No need to set.

	// Set data length to 24bit
	i2s_peripheral->I2SCFGR |= SPI_I2SCFGR_DATLEN_0;
	// Channel length automatically set to 32bit if data len > 16bit. No need to set.


	i2s_peripheral->I2SCFGR |= SPI_I2SCFGR_I2SE;

	while (!(SPI3->SR & SPI_SR_TXE));
	i2s_peripheral->DR = 0xDEAD;
}