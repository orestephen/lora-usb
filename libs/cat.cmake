cmake_minimum_required(VERSION 3.16)

include(FetchContent)
Set(FETCHCONTENT_QUIET FALSE)

FetchContent_Declare(
    cat
    GIT_REPOSITORY https://github.com/marcinbor85/cAT.git
    GIT_TAG 84fdca960b8cbc8c4b5d87cd1805815ca2a27b52
    GIT_PROGRESS TRUE
)

FetchContent_GetProperties(cat)
if(NOT cat_POPULATED)
    FetchContent_Populate(cat)
 
endif()

FetchContent_MakeAvailable(cat)

target_include_directories(${APP} PUBLIC
    ${cat_SOURCE_DIR}/src
)

target_sources(${APP} PUBLIC
    ${cat_SOURCE_DIR}/src/cat.c
)

