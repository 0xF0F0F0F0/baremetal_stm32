add_library(modules OBJECT 
    src/serial.c
    src/core_clock.c
)

target_include_directories(modules PUBLIC 
    inc
    ../device/inc
    ${CMSIS_DIR}
)
