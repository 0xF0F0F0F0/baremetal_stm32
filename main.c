#include "main.h"
#include "stm32f4xx.h"
#include "errors.h"
#include "serial.h"
#include "core_clock.h"

extern uint32_t core_clock_speed;

void setup()
{
    core_clock_init();    
}

int main(void)
{
    volatile uint32_t i = core_clock_speed;

    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;
    GPIOG->MODER |= GPIO_MODER_MODER13_0;

    setup();

    while(1)
    {   
        GPIOG->ODR ^= GPIO_ODR_ODR_13;        
        
        for(volatile uint32_t delay = 0; delay < 180000000; delay++)
            __asm__("nop");
        
    }

}