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


int16_t tx_buffer[2][4];
int16_t rx_buffer[2][4];


void DMA1_Stream2_IRQHandler(void)
{
	// In double buffer mode, DMA automatically switches the target memory to be filled.
	// Process the buffer that is NOT the current target being filled by DMA.
	bool ct = !(DMA1_Stream2->CR & DMA_SxCR_CT);

	// Reconstruct 16-bit High and Low words into single 24-bit word
	int l_in = (int) (rx_buffer[ct][0] << 16) | rx_buffer[ct][1];
	int r_in = (int) (rx_buffer[ct][2] << 16) | rx_buffer[ct][3];
	int l_out, r_out;

	// Process
	l_out = l_in;
	r_out = r_in;

	// Deconstruct single 24-bit word into 16-bit High and Low words.
	tx_buffer[ct][0] = (l_out >> 16) & 0xFFFF;
	tx_buffer[ct][1] = l_out & 0xFFFF;
	tx_buffer[ct][2] = (r_out >> 16) & 0xFFFF;
	tx_buffer[ct][3] = r_out & 0xFFFF;

	// Clear transfer complete interrupt flag
	DMA1->LIFCR |= DMA_LIFCR_CTCIF2;
}

void DMA1_Stream5_IRQHandler(void)
{
	// Clear transfer complete interrupt flag
	DMA1->HIFCR |= DMA_HIFCR_CTCIF5;
}


int main(void)
{
	core_clock_init();
	systick_init();
	serial_init(BAUD_115200);

	i2s_init(SPI3, tx_buffer, rx_buffer);

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

	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;
	GPIOG->MODER |= GPIO_MODER_MODER13_0; // LED3

	basic_timer_t led3_timer;
	basic_timer_init(&led3_timer, 500);

	while (1) {

		if (basic_timer_has_elapsed(&led3_timer)) {
			if (GPIOG->ODR & GPIO_ODR_ODR_13) {
				GPIOG->BSRR |= GPIO_BSRR_BR_13;
			}
			else {
				GPIOG->BSRR |= GPIO_BSRR_BS_13;
			}
		}

		// UART test
		while (!(USART1->SR & USART_SR_TXE));
		USART1->DR = '.';
	}
}