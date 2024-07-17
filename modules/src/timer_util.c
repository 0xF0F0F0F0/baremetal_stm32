#include "timer_util.h"
#include "core_clock.h"

volatile uint32_t systick_counter = 0;

void SysTick_Handler(void) {
    // Increment systick_counter global every 1 ms
    systick_counter++;
}

err_t systick_init(void) {
    // Enable the interrupt and start the SysTick timer (1 ms ticks)
    if(SysTick_Config((uint32_t)(CORE_CLOCK_SPEED/1000UL)) == 1) {
          return ERR1;
    }
    else return EOK;
}

uint32_t systick_get_ticks(void) {
     return systick_counter;
}

void basic_timer_init(basic_timer_t* timer, uint32_t wait_time) {
     timer->curr_ticks = 0;
     timer->prev_ticks = 0;
     timer->wait_time = wait_time;
}

bool basic_timer_has_elapsed(basic_timer_t* timer) {
     timer->curr_ticks = systick_get_ticks();
     if((timer->curr_ticks - timer->prev_ticks) >= timer->wait_time) {
          timer->prev_ticks = timer->curr_ticks;
          return true;
     }
     else return false;
}

/*--------------------- WIP ------------------------- */
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
