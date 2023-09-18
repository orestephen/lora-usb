cmake_minimum_required(VERSION 3.16)

set(APP "lora-usb")

add_executable(${APP})

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ARM)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(TOOLCHAIN_PREFIX arm-none-eabi-)

set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}g++)
set(CMAKE_ASM_COMPILER ${TOOLCHAIN_PREFIX}gcc)
set(CMAKE_OBJCOPY ${TOOLCHAIN_PREFIX}objcopy)
set(CMAKE_OBJDUMP ${TOOLCHAIN_PREFIX}objdump)
set(CMAKE_SIZE ${TOOLCHAIN_PREFIX}size)

set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")

set(TARGET "STM32F756ZG")
include(${CMAKE_SOURCE_DIR}/libs/stm32f7.cmake)
include(${CMAKE_SOURCE_DIR}/libs/stm32_usb.cmake)

project(${APP} C CXX ASM)

get_filename_component(LINKER_SCRIPT src/nucleo-f756zg/STM32F756ZGTx_FLASH.ld ABSOLUTE)

target_include_directories(${APP} PUBLIC
    src/nucleo-f756zg
    src
)

target_sources(${APP} PUBLIC
    src/nucleo-f756zg/gpio.c
    src/nucleo-f756zg/nucleo-f756zg.c
    src/nucleo-f756zg/spi.c
    src/nucleo-f756zg/stm32f7xx_hal_msp.c
    src/nucleo-f756zg/stm32f7xx_it.c
    src/nucleo-f756zg/usb_device.c
    src/nucleo-f756zg/usbd_cdc_if.c
    src/nucleo-f756zg/usbd_conf.c
    src/nucleo-f756zg/usbd_desc.c

    src/main.c
)

target_compile_options(${APP} PUBLIC
    "-fstack-usage"
    "-fdata-sections"
    "-ffunction-sections"
    "--save-temps"
    "-O0"
    "-g3"
    "-gdwarf-2"
)

target_link_options(${APP} PUBLIC
    -Wall
    --specs=nosys.specs
    -Wl,--cref,--no-warn-mismatch,--gc-sections,-Map=${APP}.map
    -T${LINKER_SCRIPT}
    "-fstack-usage"
    "-fdata-sections"
    "-ffunction-sections"
    "-Og"
    "-g3"
    "-gdwarf-2"
)

if(CMAKE_C_COMPILER_VERSION VERSION_GREATER "13")
target_link_options(${APP} PUBLIC
    "LINKER:--no-warn-rwx-segments"
)
endif()

set(SUFFIX "elf")

set_target_properties(${APP} PROPERTIES SUFFIX ".${SUFFIX}")

add_custom_command(TARGET ${APP} POST_BUILD
    COMMAND ${CMAKE_SIZE} --format=berkeley ${APP}.${SUFFIX}
)

add_custom_command(TARGET ${APP} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary ${APP}.${SUFFIX} ${APP}.bin
)

