cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME heartrate)
project(${PROJECT_NAME})

include_directories(
    include
    )

set(SOURCES
    src/HeartBeatRateTypes.cpp
    src/HeartRateTools.cpp
    src/NV21FrameSource.cpp
    src/RGBFrameSource.cpp
    src/HeartRateCounter.cpp
    src/RGBHeartRateGenerator.cpp
    src/dummys/SimpleHeartRateGenerator.cpp
    src/dummys/SimpleHeartRateVisualizer.cpp
    src/dummys/DummyRGBFrameSource.cpp
    src/dummys/DummyNV21FrameSource.cpp
    )

if(PNG_FOUND)
    set(SOURCES ${SOURCES}
        src/RGB2PNGDataBaseFrameDrawer.cpp
        )
endif(PNG_FOUND)

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

set(LIBS ${Boost_LIBRARIES})

if(PNG_FOUND)
    set(LIBS ${LIBS} ${PNG_LIBRARIES})
endif(PNG_FOUND)

target_link_libraries(${PROJECT_NAME} ${LIBS})
