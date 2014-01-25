cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME heartbeatrate)
project(${PROJECT_NAME})

include_directories(include)

set(SOURCES
    src/HeartRateProcessor.cpp
    src/RGBFrameSource.cpp
    )

add_library(${PROJECT_NAME} ${SOURCES})

if(ANDROID)
    set(LIBS 
        boost_system-gcc-mt-1_55
        boost_thread-gcc-mt-1_55
        )
else()
    set(LIBS
        boost_system.a
        boost_thread.a
        )
endif()
target_link_libraries(${PROJECT_NAME} ${LIBS})
