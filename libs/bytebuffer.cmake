cmake_minimum_required(VERSION 3.16)

include(FetchContent)
Set(FETCHCONTENT_QUIET FALSE)

FetchContent_Declare(
    bytebuffer
    GIT_REPOSITORY https://github.com/hawstan/ByteBuffer.git
    GIT_TAG f8bee35505e6ebd332dcf6d7041e7d37c512556a
    GIT_PROGRESS TRUE
)

FetchContent_GetProperties(bytebuffer)
if(NOT bytebuffer_POPULATED)
    FetchContent_Populate(bytebuffer)
 
endif()

FetchContent_MakeAvailable(bytebuffer)

target_include_directories(${APP} PUBLIC
    ${bytebuffer_SOURCE_DIR}
)

target_sources(${APP} PUBLIC
    ${bytebuffer_SOURCE_DIR}/ByteBuffer.c
)

