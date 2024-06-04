#include "main.h"
#include "stm32f4xx.h"

int main(void)
{  
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;
    GPIOG->MODER |= GPIO_MODER_MODER13_0;
    //GPIOG->OTYPER &= ~(GPIO_OTYPER_OT_13);
    //GPIOG->PUPDR &= ~(GPIO_PUPDR_PUPDR13_0);

    while(1)
    {   
        int32_t delay = 0;

        GPIOG->BSRR &= ~(GPIO_BSRR_BS_13);
        GPIOG->BSRR |= GPIO_BSRR_BR_13;
        
        for(delay = 0; delay < 3600000; delay++)
            __asm__("nop");

        GPIOG->BSRR |= GPIO_BSRR_BS_13;
        GPIOG->BSRR &= ~(GPIO_BSRR_BR_13);
        
        for(delay = 0; delay < 3600000; delay++)
            __asm__("nop");
    }

}
