#include "stm32f4xx.h"
#include "errors.h"
#include "serial.h"
#include "core_clock.h"
#include "timer_util.h"

void setup()
{   
    core_clock_init(); 
    systick_start(); 
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;
    GPIOG->MODER |= GPIO_MODER_MODER13_0;
}

int main(void)
{
    setup();
    
    while(1)
    {  
        // Blink LED every 1s (non-blocking)
        if(systick_elapsed(1000)) {
            if(GPIOG->ODR & GPIO_ODR_ODR_13) {
                GPIOG->BSRR |= GPIO_BSRR_BR_13;
            }
            else {
                GPIOG->BSRR |= GPIO_BSRR_BS_13;
            } 
        }
    }
}