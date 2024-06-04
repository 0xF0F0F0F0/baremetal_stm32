add_library(device OBJECT 
    src/startup_stm32f429.c
    src/system_stm32f4xx.c
)

target_include_directories(device PUBLIC 
    inc
    ${CMSIS_DIR}
)
