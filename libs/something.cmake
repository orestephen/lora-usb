cmake_minimum_required(VERSION 3.16)

include(FetchContent)
Set(FETCHCONTENT_QUIET FALSE)

FetchContent_Declare(
    at_interpreter
    GIT_REPOSITORY https://github.com/Shylock-Hg/AT-interpreter.git
    GIT_TAG b9838b4605a397332733e0e3be455ba805a5d71f
    GIT_PROGRESS TRUE
)

FetchContent_GetProperties(at_interpreter)
if(NOT at_interpreter_POPULATED)
    FetchContent_Populate(at_interpreter)
endif()

FetchContent_MakeAvailable(at_interpreter)

target_include_directories(${APP} PUBLIC
    ${at_interpreter_SOURCE_DIR}/inc
)

target_sources(${APP} PUBLIC
    ${at_interpreter_SOURCE_DIR}/src/at_command.c
    ${at_interpreter_SOURCE_DIR}/src/at_fsm.c
    ${at_interpreter_SOURCE_DIR}/src/at_param.c
    ${at_interpreter_SOURCE_DIR}/src/at_table.c
    ${at_interpreter_SOURCE_DIR}/src/at_xrecord.c
    ${at_interpreter_SOURCE_DIR}/src/hash.c
    ${at_interpreter_SOURCE_DIR}/src/queue.c
    ${at_interpreter_SOURCE_DIR}/src/stdlog.c
)

