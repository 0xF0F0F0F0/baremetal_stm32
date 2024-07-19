#include "core_clock.h"

/**
 * STM32F429 max clock frequencies (do not exceed these in software!)
 * AHB - 180 MHz
 * APB2 - 90 MHz
 * APB1 - 45 MHz
 *
 * --- HSE [8] -> /PLLM (in div.) [8] -> xPLLN (PLL mult.) [360] -> /PLLP (out div.) [2]
 * --- (8 MHz / 8) * 360 / 2 = 180 MHz
 *
 * To achieve 180 MHz system clock with an 8MHz HSE oscillator,
 * PLLM divider should reduce HSE to 2MHz (low PLL jitter) but for now we reduce to 1MHz,
 * (ST says PLLM should be equal to crystal frequency).
 * Followed by setting PLLN between 50 and 432 such that VCO output frequency
 * is between 100 and 432 MHz.
 * Note: With a 180 MHz PLL clock, we can't generate the 48MHz for USB OTG FS
 *       this can be done with a 168 MHz sysclock if required.
 *
 * We also need to set the internal voltage regulator to overdrive mode
 * and use 5 wait states of FLASH latency.
 */

uint32_t core_clock_speed;

err_t core_clock_init()
{
	err_t error = ERR1;

	// Set HSE (high speed external crystal @ 8MHz) as PLL source
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSE;

	// Set PLLM to 8
	RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLM); 		// Clear bits 0-5
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLM_3;

	// Set PLLN to 360
	RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLN); 		// Clear bits 6-14
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLN_3 |
			RCC_PLLCFGR_PLLN_5 |
			RCC_PLLCFGR_PLLN_6 |
			RCC_PLLCFGR_PLLN_8;

	// Set PLLP to 2
	RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLP); 		// Clear bits 16-17

	// Set PLLQ to 8 (results in 45 MHz, but need 48MHz for USB FS.)
	RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLQ); 		// Clear bits 16-17
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLQ_3;

	RCC->CR |= RCC_CR_PLLON; 			// enable PLL

	RCC->APB1ENR |= RCC_APB1ENR_PWREN; 		// enable clock to PWR interface
	PWR->CR |= PWR_CR_ODEN;			   	// enable overdrive
	while (!(PWR->CSR & PWR_CSR_ODRDY));		// wait till overdrive is ready
	PWR->CR |= PWR_CR_ODSWEN;			// switch to overdrive mode
	while (!(PWR->CSR & PWR_CSR_ODSWRDY)); 		// wait till switch

	// Set 5 wait states and enable prefetch + cache
	FLASH->ACR |= FLASH_ACR_PRFTEN |
			FLASH_ACR_ICEN |
			FLASH_ACR_DCEN;
	FLASH->ACR |= FLASH_ACR_LATENCY_5WS;

	// Set AHB and APB prescalers
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV4; 		// APB1 low speed
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV2; 		// APB2 high speed
	// AHB prescaler = 0 default

	RCC->CR |= RCC_CR_HSEON; 			// Enable HSE
	while (!(RCC->CR & RCC_CR_HSERDY)); 		// Wait till HSE is ready

	while (!(RCC->CR & RCC_CR_PLLRDY)); 		// Wait till PLL is ready

	RCC->CFGR |= RCC_CFGR_SW_PLL; 			// Set PLL as sysclock source

	RCC->CR &= ~(RCC_CR_HSION); 			// Turn off HSI oscillator

	error = EOK;
	return error;
}