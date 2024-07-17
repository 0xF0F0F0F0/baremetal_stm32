#ifndef INC_TIMER_UTIL_H
#define INC_TIMER_UTIL_H

#include "stm32f4xx.h"
#include "errors.h"
#include <stdbool.h>

err_t systick_init(void);
uint32_t systick_get_ticks(void);

typedef struct basic_timer_t{
     uint32_t curr_ticks;
     uint32_t prev_ticks;
     uint32_t wait_time;
} basic_timer_t;

void basic_timer_init(basic_timer_t* timer, uint32_t wait_time);
bool basic_timer_has_elapsed(basic_timer_t* timer);

err_t timer_start(TIM_TypeDef *TIMx, uint16_t ms); 

#endif  //INC_TIMER_UTIL_H