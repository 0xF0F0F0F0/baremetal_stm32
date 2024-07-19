#include "stm32f4xx.h"
#include "errors.h"
#include "serial.h"
#include "core_clock.h"
#include "timer_util.h"
#include "i2c.h"

int main(void)
{
	core_clock_init();
	systick_init();
	serial_init(BAUD_115200);

	volatile err_t i2c_error;
	i2c_peripheral_t i2c2 = {I2C2, true};
	i2c_peripheral_init(&i2c2);

	// Write to WM8731 codec registers
	uint8_t cmd_list[] = {
		0b00001100, 0b00010010, // power1
		0b00000000, 0b00010111, // left linein
		0b00000000, 0b00010111, // right linein
		0b00001000, 0b00010010, // analog path
		0b00001010, 0b00000000, // digital path
		0b00001110, 0b01000010, // interface
		0b00010010, 0b00000001, // active
		0b00001100, 0b00000010  // power2
	};
	uint32_t num_cmd = sizeof(cmd_list) / sizeof(uint8_t);

	i2c_error = i2c_send(&i2c2, 0x1A, cmd_list, num_cmd);

	while (1) {

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