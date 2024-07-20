add_library(modules OBJECT
    src/serial.c
    src/core_clock.c
    src/timer_util.c
    src/i2c.c
    src/i2s.c
    src/wm8731.c
)

target_include_directories(modules PUBLIC
    inc
    ${CMSIS_DIR}
    ${DEVICE_DIR}
)
