#ifndef INC_TIMER_UTIL_H
#define INC_TIMER_UTIL_H

#include "stm32f4xx.h"
#include "errors.h"
#include <stdbool.h>

err_t systick_start(void);
uint32_t systick_get_ticks(void);
bool systick_elapsed(uint32_t interval_ms);
err_t timer_start(TIM_TypeDef *TIMx, uint16_t ms); 

#endif  //INC_TIMER_UTIL_H