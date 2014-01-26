cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME frame_test)
project(${PROJECT_NAME})

include_directories(../../modules/libheartbeatrate/include)

set(SOURCES
    src/main.cpp
    )
add_executable(${PROJECT_NAME} ${SOURCES})

set(LIBS
    gtest
    gtest_main
    pthread
    
    heartbeatrate
    )
target_link_libraries(${PROJECT_NAME} ${LIBS})