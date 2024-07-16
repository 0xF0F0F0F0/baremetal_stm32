#ifndef INC_CORE_CLOCK_H
#define INC_CORE_CLOCK_H

#include "stm32f4xx.h"
#include "errors.h"

#define CORE_CLOCK_SPEED 180000000
#define APB2_CLOCK_SPEED 90000000
#define APB1_CLOCK_SPEED 45000000

err_t core_clock_init();

#endif  //INC_CORE_CLOCK_H