add_library(device OBJECT 
    startup_stm32f429.c
    system_stm32f4xx.c
)

target_include_directories(device PUBLIC 
    ${CMSIS_DIR}
)
