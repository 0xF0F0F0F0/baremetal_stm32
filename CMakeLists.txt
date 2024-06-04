cmake_minimum_required(VERSION 3.22.1)
project(baremetal_stm32 LANGUAGES ASM C CXX)

# Use arm-none-eabi toolchain
set(CMAKE_ASM_COMPILER arm-none-eabi-as)
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_LINKER arm-none-eabi-ld)
set(CMAKE_AR arm-none-eabi-ar)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP arm-none-eabi-objdump)
set(CMAKE_NM arm-none-eabi-nm)
set(CMAKE_STRIP arm-none-eabi-strip)
set(CMAKE_RANLIB arm-none-eabi-ranlib)

# MCU parameters
set(MCU_ARCH    "cortex-m4")
set(MCU_PART "STM32F429_439xx")

# CMSIS directory
set(CMSIS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/CMSIS/Core/Include")

# Linker directory
set(LINKER_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/device/gcc_arm.ld")


# Sources
set(SOURCES 
    main.c
)

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

# This prevents linker from "-rdynamic" error.
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS   "")
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")
set(CMAKE_EXE_LINKER_FLAGS "-T${LINKER_SCRIPT} -Wl,-Map=${PROJECT_NAME}.map")

set(CMAKE_C_FLAGS  "-mcpu=${MCU_ARCH}   \
                    -D${MCU_PART}       \
                    -mthumb             \
                    -mfloat-abi=hard    \
                    -mfpu=fpv4-sp-d16   \
                    --specs=nosys.specs \
                    -O3")

set(CMAKE_CXX_FLAGS ${CMAKE_C_FLAGS})

add_subdirectory(device)
add_executable(${PROJECT_NAME}.elf ${SOURCES})
target_link_libraries(${PROJECT_NAME}.elf PRIVATE device)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${PROJECT_NAME}.elf> ${CMAKE_CURRENT_SOURCE_DIR}/bin/${PROJECT_NAME}.bin
)
