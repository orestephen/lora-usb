cmake_minimum_required(VERSION 3.16)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

FetchContent_Declare(
  sx126x_driver
  GIT_REPOSITORY https://github.com/Lora-net/sx126x_driver.git
  GIT_TAG 6980c951345fc1dd5b4566da6aafc12710797350
  GIT_SHALLOW 1
  GIT_PROGRESS TRUE)

FetchContent_MakeAvailable(sx126x_driver)

target_include_directories(${PROJECT_NAME}
                           PUBLIC ${sx126x_driver_SOURCE_DIR}/src)

target_sources(
  ${PROJECT_NAME}
  PUBLIC ${sx126x_driver_SOURCE_DIR}/src/lr_fhss_mac.c
         ${sx126x_driver_SOURCE_DIR}/src/sx126x.c
         ${sx126x_driver_SOURCE_DIR}/src/sx126x_driver_version.c
         ${sx126x_driver_SOURCE_DIR}/src/sx126x_lr_fhss.c)
