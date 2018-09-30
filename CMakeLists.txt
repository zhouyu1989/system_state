cmake_minimum_required(VERSION 2.8)

project(system_state)

SET(SRC_LIST src/SystemInfo.cpp
        src/SystemState.cpp
        src/rk_sys_status.cpp
        )


add_library(systemstate SHARED ${SRC_LIST})
add_executable(systemstate_test ${SRC_LIST} test/test.cpp)
