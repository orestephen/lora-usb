cmake_minimum_required(VERSION 3.16)

include(FetchContent)
Set(FETCHCONTENT_QUIET FALSE)

FetchContent_Declare(
    cmsis_core
    GIT_REPOSITORY https://github.com/STMicroelectronics/cmsis_core.git
    GIT_TAG 96d6da4e252b06dcfdc041e7df23e86161c33007
    GIT_PROGRESS TRUE
)

FetchContent_Declare(
    cmsis_device_f7
    GIT_REPOSITORY https://github.com/STMicroelectronics/cmsis_device_f7.git
    GIT_TAG 25b0463439303b7a38f0d27b161f7d2f3c096e79
    GIT_PROGRESS TRUE
)

FetchContent_Declare(
    stm32f7xx_hal_driver
    GIT_REPOSITORY https://github.com/STMicroelectronics/stm32f7xx_hal_driver.git
    GIT_TAG e61e3036e0ae928a58d64b07ea3550b209b473bc
    GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(cmsis_core)
FetchContent_MakeAvailable(cmsis_device_f7)
FetchContent_MakeAvailable(stm32f7xx_hal_driver)

target_include_directories(${APP} PUBLIC
    ${cmsis_core_SOURCE_DIR}/Include
    ${cmsis_device_f7_SOURCE_DIR}/Include
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Inc
)

set(STM32F7_LIST
    STM32F756
    STM32F746
    STM32F745
    STM32F765
    STM32F767
    STM32F769
    STM32F777
    STM32F779
    STM32F722
    STM32F723
    STM32F732
    STM32F733
    STM32F730
    STM32F750
)

foreach (ITEM IN LISTS STM32F7_LIST)
    if (${TARGET} MATCHES "${ITEM}")
        set(TARGET_STM32 "${ITEM}xx")
        message("TARGET_STM32: ${TARGET_STM32}")
    endif()
endforeach()

string(TOLOWER ${TARGET_STM32} TARGET_STM32_LOWER)

target_sources(${APP} PUBLIC
    ${cmsis_device_f7_SOURCE_DIR}/Source/Templates/gcc/startup_${TARGET_STM32_LOWER}.s
    ${cmsis_device_f7_SOURCE_DIR}/Source/Templates/system_stm32f7xx.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_adc.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_adc_ex.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_can.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_cec.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_cortex.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_crc.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_crc_ex.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_cryp.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_cryp_ex.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_dac.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_dac_ex.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_dcmi.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_dcmi_ex.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_dfsdm.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_dma2d.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_dma.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_dma_ex.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_dsi.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_eth.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_exti.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_flash.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_flash_ex.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_gpio.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_hash.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_hash_ex.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_hcd.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_i2c.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_i2c_ex.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_i2s.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_irda.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_iwdg.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_jpeg.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_lptim.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_ltdc.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_ltdc_ex.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_mdios.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_mmc.c
    # ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_msp_template.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_nand.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_nor.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_pcd.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_pcd_ex.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_pwr.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_pwr_ex.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_qspi.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_rcc.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_rcc_ex.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_rng.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_rtc.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_rtc_ex.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_sai.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_sai_ex.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_sd.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_sdram.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_smartcard.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_smartcard_ex.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_smbus.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_spdifrx.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_spi.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_spi_ex.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_sram.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_tim.c
    # ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_timebase_rtc_alarm_template.c
    # ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_timebase_rtc_wakeup_template.c
    # ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_timebase_tim_template.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_tim_ex.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_uart.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_uart_ex.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_usart.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_wwdg.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_ll_adc.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_ll_crc.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_ll_dac.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_ll_dma2d.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_ll_dma.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_ll_exti.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_ll_fmc.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_ll_gpio.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_ll_i2c.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_ll_lptim.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_ll_pwr.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_ll_rcc.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_ll_rng.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_ll_rtc.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_ll_sdmmc.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_ll_spi.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_ll_tim.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_ll_usart.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_ll_usb.c
    ${stm32f7xx_hal_driver_SOURCE_DIR}/Src/stm32f7xx_ll_utils.c
)

target_compile_options(${APP} PUBLIC
    "-mcpu=cortex-m7"
    "-mthumb"
    "-mfpu=fpv5-sp-d16"
    "-mfloat-abi=hard"
)

target_link_options(${APP} PUBLIC
    "-mcpu=cortex-m7"
    "-mthumb"
    "-mfpu=fpv5-sp-d16"
    "-mfloat-abi=hard"
)

target_compile_definitions(${APP} PUBLIC
    USE_HAL_DRIVER
    ${TARGET_STM32}
)
