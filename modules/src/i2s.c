#include "i2s.h"

/**
 * SPI3 - I2S3 (TX/DAC data), I2S3ext (RX/ADC data) full-duplex
 *
 * LRCK - PA4 - altfunc 6
 * SCK - PB3 - altfunc 6
 * SD - (SO on board, DAC data) - PB5 - altfunc 6
 * SD_ext - (SI on board, ADC data) - PB4 - altfunc 7
 */



static void dma_init(int16_t (*tx_buffer)[4], int16_t (*rx_buffer)[4])
{
	RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;


	// ------------------------ I2S3ext_RX -> DMA1 Stream 2 Channel 2 ---------------------------//
	DMA1_Stream2->CR &= ~(DMA_SxCR_EN);		// disable stream
	while(DMA1_Stream2->CR & DMA_SxCR_EN);		// wait and ensure stream is disabled
	DMA1_Stream2->PAR = (uint32_t)&I2S3ext->DR;	// base address of I2S3ext->DR
	DMA1_Stream2->M0AR = (uint32_t)rx_buffer[0];	// first buffer address
	DMA1_Stream2->M1AR = (uint32_t)rx_buffer[1];	// second buffer address
	DMA1_Stream2->NDTR = 4;				// number of transfers per request
	DMA1_Stream2->CR |= DMA_SxCR_CHSEL_1;		// channel 2
	DMA1_Stream2->CR |= DMA_SxCR_DBM;		// double buffer mode
	//DMA1_Stream2->CR |= DMA_SxCR_PL_1;		// high priority
	DMA1_Stream2->CR |= DMA_SxCR_MSIZE_0;		// memory data size: half-word (16-bit)
	DMA1_Stream2->CR |= DMA_SxCR_PSIZE_0;		// peripheral data size: half-word (16-bit)
	DMA1_Stream2->CR |= DMA_SxCR_MINC;		// memory address incremented
	// direction: peripheral -> memory (default)
	DMA1_Stream2->CR |= DMA_SxCR_TCIE;		// transfer complete interrupt enable
	NVIC_SetPriority(DMA1_Stream2_IRQn, 14);
	NVIC_EnableIRQ(DMA1_Stream2_IRQn);		// enable DMA1 stream 2 global interrupt


	// ------------------------ SPI3_TX -> DMA1 Stream 5 Channel 0 -----------------------------//
	DMA1_Stream5->CR &= ~(DMA_SxCR_EN);		// disable stream
	while(DMA1_Stream5->CR & DMA_SxCR_EN);		// wait and ensure stream is disabled
	DMA1_Stream5->PAR = (uint32_t)&SPI3->DR;	// base address of SPI3->DR
	DMA1_Stream5->M0AR = (uint32_t)tx_buffer[0];	// first buffer address
	DMA1_Stream5->M1AR = (uint32_t)tx_buffer[1];	// second buffer address
	DMA1_Stream5->NDTR = 4;				// number of transfers per request
	// channel 0 (default)
	DMA1_Stream5->CR |= DMA_SxCR_DBM;		// double buffer mode
	//DMA1_Stream5->CR |= DMA_SxCR_PL_1;		// high priority
	DMA1_Stream5->CR |= DMA_SxCR_MSIZE_0;		// memory data size: half-word (16-bit)
	DMA1_Stream5->CR |= DMA_SxCR_PSIZE_0;		// peripheral data size: half-word (16-bit)
	DMA1_Stream5->CR |= DMA_SxCR_MINC;		// memory address incremented
	DMA1_Stream5->CR |= DMA_SxCR_DIR_0;		// direction: memory -> peripheral
	DMA1_Stream5->CR |= DMA_SxCR_TCIE;		// transfer complete interrupt enable
	NVIC_SetPriority(DMA1_Stream5_IRQn, 15);
	NVIC_EnableIRQ(DMA1_Stream5_IRQn);		// enable DMA1 stream 5 global interrupt

	DMA1_Stream2->CR |= DMA_SxCR_EN;		// enable stream 2 (RX)
	DMA1_Stream5->CR |= DMA_SxCR_EN;		// enable stream 5 (TX)
}

err_t i2s_init(SPI_TypeDef* i2s_peripheral, int16_t (*tx_buffer)[4], int16_t (*rx_buffer)[4])
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

	I2S3ext->I2SCFGR |= SPI_I2SCFGR_I2SMOD;		// enable i2s mode
	I2S3ext->I2SCFGR |= SPI_I2SCFGR_I2SCFG_0;	// slave receiver
	I2S3ext->I2SCFGR |= SPI_I2SCFGR_DATLEN_0;	// 24-bit



	// Set data length to 24bit
	i2s_peripheral->I2SCFGR |= SPI_I2SCFGR_DATLEN_0;
	// Channel length automatically set to 32bit if data len > 16bit. No need to set.

	dma_init(tx_buffer, rx_buffer);

	// Enable DMA requests
	i2s_peripheral->CR2 |= SPI_CR2_TXDMAEN;
	I2S3ext->CR2 |= SPI_CR2_RXDMAEN;

	// Enable I2S interface
	i2s_peripheral->I2SCFGR |= SPI_I2SCFGR_I2SE;
	I2S3ext->I2SCFGR |= SPI_I2SCFGR_I2SE;
}