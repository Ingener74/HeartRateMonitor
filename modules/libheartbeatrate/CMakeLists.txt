cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME heartbeatrate)
project(${PROJECT_NAME})

include_directories(
    include
    )

set(SOURCES
    src/HeartBeatRateTypes.cpp
    src/HeartRateTools.cpp
    src/NV21FrameSource.cpp
    src/RGBFrameSource.cpp
    src/SimpleHeartRateGenerator.cpp
    src/SimpleHeartRateVisualizer.cpp
    src/HeartRateCounter.cpp
    src/RGBHeartRateGenerator.cpp
    )

if(ANDROID)
    set(SOURCES ${SOURCES}
        src/log/AndroidLog.cpp
        )
else()
    set(SOURCES ${SOURCES}
        src/log/LinuxLog.cpp
        )
endif()

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
