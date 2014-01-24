cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME frame)
project(${PROJECT_NAME})

include_directories(include)

set(SOURCES
    src/RGBFrameSource.cpp
    )

add_library(${PROJECT_NAME} ${SOURCES})

set(LIBS
    boost_system-gcc-mt-1_55
    boost_thread-gcc-mt-1_55
    )
    
target_link_libraries(${PROJECT_NAME} ${LIBS})