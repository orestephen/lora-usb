cmake_minimum_required(VERSION 3.16)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

FetchContent_Declare(
  stm32_usb_device
  GIT_REPOSITORY https://github.com/STMicroelectronics/stm32_mw_usb_device.git
  GIT_TAG 2022e75b01a499b17acd17d28691b1ed5bbef2dc
  GIT_PROGRESS TRUE)

FetchContent_MakeAvailable(stm32_usb_device)

target_include_directories(
  ${PROJECT_NAME}
  PUBLIC ${stm32_usb_device_SOURCE_DIR}/Class/AUDIO/Inc
         ${stm32_usb_device_SOURCE_DIR}/Class/BillBoard/Inc
         ${stm32_usb_device_SOURCE_DIR}/Class/CCID/Inc
         ${stm32_usb_device_SOURCE_DIR}/Class/CDC/Inc
         ${stm32_usb_device_SOURCE_DIR}/Class/CDC_ECM/Inc
         ${stm32_usb_device_SOURCE_DIR}/Class/CDC_RNDIS/Inc
         ${stm32_usb_device_SOURCE_DIR}/Class/CompositeBuilder/Inc
         ${stm32_usb_device_SOURCE_DIR}/Class/CustomHID/Inc
         ${stm32_usb_device_SOURCE_DIR}/Class/DFU/Inc
         ${stm32_usb_device_SOURCE_DIR}/Class/HID/Inc
         ${stm32_usb_device_SOURCE_DIR}/Class/MSC/Inc
         ${stm32_usb_device_SOURCE_DIR}/Class/MTP/Inc
         ${stm32_usb_device_SOURCE_DIR}/Class/Printer/Inc
         ${stm32_usb_device_SOURCE_DIR}/Class/Template/Inc
         ${stm32_usb_device_SOURCE_DIR}/Class/VIDEO/Inc
         ${stm32_usb_device_SOURCE_DIR}/Core/Inc)

target_sources(
  ${PROJECT_NAME}
  PUBLIC
    ${stm32_usb_device_SOURCE_DIR}/Class/AUDIO/Src/usbd_audio.c
    # ${stm32_usb_device_SOURCE_DIR}/Class/AUDIO/Src/usbd_audio_if_template.c
    ${stm32_usb_device_SOURCE_DIR}/Class/BillBoard/Src/usbd_billboard.c
    ${stm32_usb_device_SOURCE_DIR}/Class/CCID/Src/usbd_ccid.c
    ${stm32_usb_device_SOURCE_DIR}/Class/CCID/Src/usbd_ccid_cmd.c
    # ${stm32_usb_device_SOURCE_DIR}/Class/CCID/Src/usbd_ccid_if_template.c
    # ${stm32_usb_device_SOURCE_DIR}/Class/CCID/Src/usbd_ccid_sc_if_template.c
    # ${stm32_usb_device_SOURCE_DIR}/Class/CCID/Src/usbd_ccid_smartcard_template.c
    ${stm32_usb_device_SOURCE_DIR}/Class/CDC/Src/usbd_cdc.c
    # ${stm32_usb_device_SOURCE_DIR}/Class/CDC/Src/usbd_cdc_if_template.c
    ${stm32_usb_device_SOURCE_DIR}/Class/CDC_ECM/Src/usbd_cdc_ecm.c
    # ${stm32_usb_device_SOURCE_DIR}/Class/CDC_ECM/Src/usbd_cdc_ecm_if_template.c
    ${stm32_usb_device_SOURCE_DIR}/Class/CDC_RNDIS/Src/usbd_cdc_rndis.c
    # ${stm32_usb_device_SOURCE_DIR}/Class/CDC_RNDIS/Src/usbd_cdc_rndis_if_template.c
    ${stm32_usb_device_SOURCE_DIR}/Class/CompositeBuilder/Src/usbd_composite_builder.c
    ${stm32_usb_device_SOURCE_DIR}/Class/CustomHID/Src/usbd_customhid.c
    # ${stm32_usb_device_SOURCE_DIR}/Class/CustomHID/Src/usbd_customhid_if_template.c
    ${stm32_usb_device_SOURCE_DIR}/Class/DFU/Src/usbd_dfu.c
    # ${stm32_usb_device_SOURCE_DIR}/Class/DFU/Src/usbd_dfu_media_template.c
    ${stm32_usb_device_SOURCE_DIR}/Class/HID/Src/usbd_hid.c
    ${stm32_usb_device_SOURCE_DIR}/Class/MSC/Src/usbd_msc_bot.c
    ${stm32_usb_device_SOURCE_DIR}/Class/MSC/Src/usbd_msc.c
    ${stm32_usb_device_SOURCE_DIR}/Class/MSC/Src/usbd_msc_data.c
    ${stm32_usb_device_SOURCE_DIR}/Class/MSC/Src/usbd_msc_scsi.c
    # ${stm32_usb_device_SOURCE_DIR}/Class/MSC/Src/usbd_msc_storage_template.c
    ${stm32_usb_device_SOURCE_DIR}/Class/MTP/Src/usbd_mtp.c
    # ${stm32_usb_device_SOURCE_DIR}/Class/MTP/Src/usbd_mtp_if_template.c
    ${stm32_usb_device_SOURCE_DIR}/Class/MTP/Src/usbd_mtp_opt.c
    ${stm32_usb_device_SOURCE_DIR}/Class/MTP/Src/usbd_mtp_storage.c
    ${stm32_usb_device_SOURCE_DIR}/Class/Printer/Src/usbd_printer.c
    # ${stm32_usb_device_SOURCE_DIR}/Class/Printer/Src/usbd_printer_if_template.c
    # ${stm32_usb_device_SOURCE_DIR}/Class/Template/Src/usbd_template.c
    ${stm32_usb_device_SOURCE_DIR}/Class/VIDEO/Src/usbd_video.c
    # ${stm32_usb_device_SOURCE_DIR}/Class/VIDEO/Src/usbd_video_if_template.c
    # ${stm32_usb_device_SOURCE_DIR}/Core/Src/usbd_conf_template.c
    ${stm32_usb_device_SOURCE_DIR}/Core/Src/usbd_core.c
    ${stm32_usb_device_SOURCE_DIR}/Core/Src/usbd_ctlreq.c
    # ${stm32_usb_device_SOURCE_DIR}/Core/Src/usbd_desc_template.c
    ${stm32_usb_device_SOURCE_DIR}/Core/Src/usbd_ioreq.c)
