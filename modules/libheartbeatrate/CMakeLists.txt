cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME heartbeatrate)
project(${PROJECT_NAME})

include_directories(include)

set(SOURCES
    src/HeartBeatRateTypes.cpp
    src/HeartRateProcessor.cpp
    src/HeartRateTools.cpp
    src/NV21FrameSource.cpp
    src/RGBFrameSource.cpp
    src/SimpleHeartRateGenerator.cpp
    src/SimpleHeartRateVisualizer.cpp
    src/HeartRateCounter.cpp
    )

if(ANDROID)
    set(SOURCES ${SOURCES}
        src/AndroidLog.cpp
        )
else()
    set(SOURCES ${SOURCES}
        src/LinuxLog.cpp
        )
endif()

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
