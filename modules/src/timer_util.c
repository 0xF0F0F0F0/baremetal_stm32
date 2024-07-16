#include "timer_util.h"
#include "core_clock.h"

volatile uint32_t systick_counter = 0;
volatile uint32_t curr_ticks, prev_ticks = 0;

void SysTick_Handler(void) {
    // Increment systick_counter global every 1 ms
    systick_counter++;
}

err_t systick_start(void) {
    // Enable the interrupt and start the SysTick timer (1 ms ticks)
    SysTick_Config((uint32_t)(CORE_CLOCK_SPEED/1000UL));
}

uint32_t systick_get_ticks(void) {
     return systick_counter;
}

bool systick_elapsed(uint32_t interval_ms) {
     curr_ticks = systick_get_ticks();
     if((curr_ticks - prev_ticks) >= interval_ms) {
          prev_ticks = curr_ticks;
          return true;
     }
     else return false;
}

err_t timer_start(TIM_TypeDef *TIMx, uint16_t ms) {
   
   RCC->DCKCFGR |= RCC_DCKCFGR_TIMPRE;                      // Clock TIMx at HCLK (core clock speed)
   
   if(TIMx == TIM2) {
        RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;                 // Enable clock to TIM2 peripheral
        TIM2->CR1 &= ~(TIM_CR1_CEN);                        // Turn off the counter
        RCC->APB1RSTR |=  (RCC_APB1RSTR_TIM2RST);           // Reset the TIM2 peripheral
        RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM2RST);           //
        TIM2->PSC = (uint16_t)0;                            // Prescaler
        TIM2->ARR = ((CORE_CLOCK_SPEED - 1) / 1000) * ms;   // Auto-reload value
        TIM2->EGR |= TIM_EGR_UG;                            // Update timer values           
        TIM2->CR1 |= TIM_CR1_CEN;                           // Start the timer
   }
   else {
        // todo: other timers
   }

     //        while(!(TIM2->SR & TIM_SR_UIF)) {}
     //        TIM2->SR &= ~(TIM_SR_UIF);
}
