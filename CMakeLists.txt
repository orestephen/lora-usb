cmake_minimum_required(VERSION 3.16)

project(lora-usb C CXX ASM)

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

add_executable(${PROJECT_NAME})

set(TARGET "STM32F756ZG")
include(${CMAKE_SOURCE_DIR}/libs/stm32f7.cmake)
include(${CMAKE_SOURCE_DIR}/libs/stm32_usb.cmake)
include(${CMAKE_SOURCE_DIR}/libs/sx126x_driver.cmake)

get_filename_component(LINKER_SCRIPT src/nucleo-f756zg/STM32F756ZGTx_FLASH.ld
                       ABSOLUTE)

target_include_directories(${PROJECT_NAME} PUBLIC src/nucleo-f756zg src/radio
                                                  src)

target_sources(
  ${PROJECT_NAME}
  PUBLIC src/nucleo-f756zg/gpio.c
         src/nucleo-f756zg/nucleo-f756zg.c
         src/nucleo-f756zg/spi.c
         src/nucleo-f756zg/stm32f7xx_hal_msp.c
         src/nucleo-f756zg/stm32f7xx_it.c
         src/nucleo-f756zg/usb_device.c
         src/nucleo-f756zg/usbd_cdc_if.c
         src/nucleo-f756zg/usbd_conf.c
         src/nucleo-f756zg/usbd_desc.c
         src/radio/apps_common.c
         src/radio/smtc_hal_dbg_trace.c
         src/radio/smtc_shield_sx1261mb2bas.c
         src/radio/sx126x_hal.c
         src/radio/sx126x_str.c
         src/main.c)

target_compile_options(
  ${PROJECT_NAME}
  PUBLIC "-fstack-usage"
         "-fdata-sections"
         "-ffunction-sections"
         "--save-temps"
         "-O0"
         "-g3"
         "-gdwarf-2")

target_link_options(
  ${PROJECT_NAME}
  PUBLIC
  -Wall
  --specs=nosys.specs
  -Wl,--cref,--no-warn-mismatch,--gc-sections,-Map=${PROJECT_NAME}.map
  -T${LINKER_SCRIPT}
  "-fstack-usage"
  "-fdata-sections"
  "-ffunction-sections"
  "-Og"
  "-g3"
  "-gdwarf-2")

if(CMAKE_C_COMPILER_VERSION VERSION_GREATER "13")
  target_link_options(${PROJECT_NAME} PUBLIC "LINKER:--no-warn-rwx-segments")
endif()

set(SUFFIX "elf")

set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".${SUFFIX}")

add_custom_command(
  TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND ${CMAKE_SIZE} --format=berkeley ${PROJECT_NAME}.${SUFFIX})

add_custom_command(
  TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND ${CMAKE_OBJCOPY} -O binary ${PROJECT_NAME}.${SUFFIX}
          ${PROJECT_NAME}.bin)
