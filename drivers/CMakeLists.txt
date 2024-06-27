add_library(drivers STATIC 
    src/stm32f4xx_rcc.c
    src/stm32f4xx_tim.c
    src/stm32f4xx_usart.c
)

target_include_directories(drivers PUBLIC 
    inc
    ../device/inc
    ${CMSIS_DIR}
)
