#include "stm32f4xx.h"
#include "errors.h"
#include "serial.h"
#include "core_clock.h"
#include "timer_util.h"
#include "i2c.h"
#include "wm8731.h"
#include "i2s.h"

/**
 * WIP! Currently testing double buffered, full-duplex I2S with DMA transfers. Passthrough Works!
 */

int16_t tx_buffer_A[4];
int16_t tx_buffer_B[4];
int16_t rx_buffer_A[4];
int16_t rx_buffer_B[4];

void DMA1_Stream2_IRQHandler(void)
{
	// I2S3 ext (RX)
	if (0 == (DMA1_Stream2->CR & DMA_SxCR_CT)) {

		int l_sample = (int) (rx_buffer_B[0] << 16) | rx_buffer_B[1];
		int r_sample = (int) (rx_buffer_B[2] << 16) | rx_buffer_B[3];

		tx_buffer_B[0] = (l_sample >> 16) & 0xFFFF;
		tx_buffer_B[1] = l_sample & 0xFFFF;
		tx_buffer_B[2] = (r_sample >> 16) & 0xFFFF;
		tx_buffer_B[3] = r_sample & 0xFFFF;
	}
	else {
		int l_sample = (int) (rx_buffer_A[0] << 16) | rx_buffer_A[1];
		int r_sample = (int) (rx_buffer_A[2] << 16) | rx_buffer_A[3];

		tx_buffer_A[0] = (l_sample >> 16) & 0xFFFF;
		tx_buffer_A[1] = l_sample & 0xFFFF;
		tx_buffer_A[2] = (r_sample >> 16) & 0xFFFF;
		tx_buffer_A[3] = r_sample & 0xFFFF;
	}
}

void DMA1_Stream5_IRQHandler(void)
{/*
	// SPI3 (TX)
	if (0 == (DMA1_Stream2->CR & DMA_SxCR_CT)) {

		int l_sample = (int) 0xAAAA;
		int r_sample = (int) 0xBBBB;

		tx_buffer_B[0] = (l_sample >> 16) & 0xFFFF;
		tx_buffer_B[1] = l_sample & 0xFFFF;
		tx_buffer_B[2] = (r_sample >> 16) & 0xFFFF;
		tx_buffer_B[3] = r_sample & 0xFFFF;
	}
	else {
		int l_sample = (int) 0xCCCC;
		int r_sample = (int) 0xDDDD;

		tx_buffer_A[0] = (l_sample >> 16) & 0xFFFF;
		tx_buffer_A[1] = l_sample & 0xFFFF;
		tx_buffer_A[2] = (r_sample >> 16) & 0xFFFF;
		tx_buffer_A[3] = r_sample & 0xFFFF;
	}

*/}


int main(void)
{
	core_clock_init();
	systick_init();
	serial_init(BAUD_115200);

	i2s_init(SPI3, tx_buffer_A, tx_buffer_B, rx_buffer_A, rx_buffer_B);

	volatile err_t i2c_error;
	i2c_peripheral_t i2c2 = {I2C2, true};
	i2c_peripheral_init(&i2c2);

	// Write to WM8731 codec registers
	uint8_t cmd_list[] = {
		0b00001100, 0b01000010, // power1
		0b00000000, 0b00010111, // left linein
		0b00000010, 0b00010111, // right linein
		0b00001000, 0b00010010, // analog path
		0b00001010, 0b00000001, // digital path
		0b00001110, 0b01000010, // interface
		0b00010010, 0b00000001 // active
		//0b00001100, 0b00000010  // power2 ?? something wrong, check
	};

	/**
	 * It seems that the i2c commands misbehave (NACKs) once the i2s clocks are enabled (crosstalk?).
	 * For now we enable the i2s clocks (interface active) at the end so that no i2c commands get
	 * corrupted. This may cause a pop since we have to enable outputs before-hand.
	 *
	 * Possible solution: use 220R series resistors on the scl and sda lines.
	 *
	 *  */

	uint32_t num_cmd = sizeof(cmd_list) / sizeof(uint8_t);

	i2c_error = wm8731_init(&i2c2, 0x1A, cmd_list, num_cmd);

	// should fill SPI3->DR once after wm8731 i2s interface is enabled.
	// To do this nicely, fill DR atleast 2 PCLKs (APB1) before the i2s driver receives
	// the first bit clock from the codec.
	//while (!(SPI3->SR & SPI_SR_TXE));
	//SPI3->DR = 0x0000;	// upper half
	//while (!(SPI3->SR & SPI_SR_TXE));
	//SPI3->DR = 0x0000;	// lower half

	// test sine wave 1kHz, 1 cycle @ 48kHz Fs
	// generated from Octave samples[x] = sin(2*pi*1000*t[x]), where t[x] = 0 : 1/Fs : 0.001
	// float value (-1 to 1) multiplied by 0x7FFFFF for converting to 24-bit signed int
	volatile int32_t samples[48] = {
	0,
	1094900,
	2171100,
	3210200,
	4194300,
	5106700,
	5931600,
	6655100,
	7264700,
	7750100,
	8102800,
	8316800,
	8388600,
	8316800,
	8102800,
	7750100,
	7264700,
	6655100,
	5931600,
	5106700,
	4194300,
	3210200,
	2171100,
	1094900,
	0,
	-1094900,
	-2171100,
	-3210200,
	-4194300,
	-5106700,
	-5931600,
	-6655100,
	-7264700,
	-7750100,
	-8102800,
	-8316800,
	-8388600,
	-8316800,
	-8102800,
	-7750100,
	-7264700,
	-6655100,
	-5931600,
	-5106700,
	-4194300,
	-3210200,
	-2171100,
	-1094900};

	int16_t received_high = 0;
	int16_t received_low = 0;

	while (1) {

		/*
		for (int i = 0; i < 48; i++) {
			for (int channel = 0; channel < 2; channel ++) {
				while(!(I2S3ext->SR & SPI_SR_RXNE));
				while (!(SPI3->SR & SPI_SR_TXE));
				SPI3->DR = I2S3ext->DR;
				while(!(I2S3ext->SR & SPI_SR_RXNE));
				while (!(SPI3->SR & SPI_SR_TXE));
				SPI3->DR = I2S3ext->DR;
				//SPI3->DR = (int16_t)((samples[i] & 0x00FFFF00) >> 8); // upper half
				//SPI3->DR = (int16_t)((samples[i] & 0x000000FF) << 8); // lower half
			}
		}
		*/
	}
}

/*
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;
	GPIOG->MODER |= GPIO_MODER_MODER13_0; // LED3
	GPIOG->MODER |= GPIO_MODER_MODER14_0; // LED4

	basic_timer_t led3_timer, led4_timer;
	basic_timer_init(&led3_timer, 500);
	basic_timer_init(&led4_timer, 1000);

	char received_byte = '\0';

	while (1) {
		if (basic_timer_has_elapsed(&led3_timer)) {
			if (GPIOG->ODR & GPIO_ODR_ODR_13) {
				GPIOG->BSRR |= GPIO_BSRR_BR_13;
			}
			else {
				GPIOG->BSRR |= GPIO_BSRR_BS_13;
			}
		}

		if (basic_timer_has_elapsed(&led4_timer)) {
			if (GPIOG->ODR & GPIO_ODR_ODR_14) {
				GPIOG->BSRR |= GPIO_BSRR_BR_14;
			}
			else {
				GPIOG->BSRR |= GPIO_BSRR_BS_14;
			}
		}

		// uart testing - blocking echo
		while (!(USART1->SR & USART_SR_RXNE));
		received_byte = USART1->DR;
		while (!(USART1->SR & USART_SR_TXE));
		USART1->DR = received_byte;
	}

*/