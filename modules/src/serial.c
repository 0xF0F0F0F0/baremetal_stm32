#include "serial.h"

/**
 * TODO: Create a module for configuring GPIO and RCC.
 */

// USART1 -> connected to USB virtual com port on STM32F429 discovery
// PA9 -> TX
// PA10 -> RX

err_t serial_init(baud_t baud_rate)
{
	err_t error = ERR1;

	// Enable clocks for USART and GPIOA (default for USART1 is peripheral clock, APB2)
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

	// Reset the peripheral
	RCC->APB2RSTR |= RCC_APB2RSTR_USART1RST;
	RCC->APB2RSTR &= ~(RCC_APB2RSTR_USART1RST);

	// Set PA9 and PA10 to alternate function AF7
	GPIOA->MODER |= (GPIO_MODER_MODER9_1 | GPIO_MODER_MODER10_1);
	GPIOA->OSPEEDR |= (GPIO_OSPEEDER_OSPEEDR9_1 | GPIO_OSPEEDER_OSPEEDR10_1);
	GPIOA->AFR[1] |= ((7 << 4) | (7 << 8));

	USART1->CR1 &= ~(USART_CR1_M);		// word length = 8
	USART1->CR2 |= USART_CR2_STOP_1;	// stop bits = 2

	switch (baud_rate) {
	case BAUD_115200:
		USART1->BRR |= (13 << BRR_FRACTION_POS);
		USART1->BRR |= (48 << BRR_MANTISSA_POS);
		break;
	default:
		USART1->BRR |= 13;		// DIV_Fraction
		USART1->BRR |= (48 << 4);	// DIV_Mantissa
	}

	// Enable UART, Tx, Rx
	USART1->CR1 |= (USART_CR1_UE | USART_CR1_TE | USART_CR1_RE);

	error = EOK;
	return error;
}

err_t serial_read_byte()
{

}