#include "core_clock.h"

/**
 * STM32F429 max clock frequencies (do not exceed this in software!)
 * AHB - 180 MHz
 * APB1 - 90 MHz
 * APB2 - 45 MHz
 *
*/

err_t core_clock_init() {

    //set HSE (external crystal @ 8MHz) as PLL source
    RCC -> PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSE;
    
    //default divider on reset is 2, x45 to get 180MHz (8MHz / 2) * 45 = 180MHz
    RCC -> PLLCFGR |= RCC_PLLCFGR_PLLN_8;

    RCC -> CR |= RCC_CR_HSEON;              //enable HSE
    while(!(RCC->CR & RCC_CR_HSERDY)) {};   //wait till HSE is ready

    RCC -> CR |= RCC_CR_PLLON;              //enable PLL
    while(!(RCC->CR & RCC_CR_PLLRDY)) {};   //wait till PLL is ready


    
}