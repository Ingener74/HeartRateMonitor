cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME heartrate)
project(${PROJECT_NAME})

set(SOURCES
    src/HeartBeatRateTypes.cpp
    src/HeartRateTools.cpp
    src/NV21FrameSource.cpp
    src/RGBFrameSource.cpp
    src/HeartRateCounter.cpp
    src/RGBHeartRateGenerator.cpp
    src/Types.cpp

    src/mocks/MockHeartRateVisualizer.cpp
    src/mocks/MockHeartRateGenerator.cpp
    src/mocks/MockNV21FrameSource.cpp
    src/mocks/MockRGBFrameSource.cpp
    src/mocks/MockHeartRateFrequencyVisualizer.cpp
    src/mocks/MockHeartRateRecognizer.cpp
    )

if(PNG_FOUND)
    set(SOURCES ${SOURCES}
        src/RGB2PNGDataBaseFrameDrawer.cpp
        src/PNGDataBase2RGBFrameSource.cpp
        )
endif(PNG_FOUND)

if(FFTW3_FOUND)
    set(SOURCES ${SOURCES}
        src/FFTWHeartRateRecognizer.cpp
    )
endif(FFTW3_FOUND)

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
    set(LIBS ${LIBS} 
        ${PNG_LIBRARIES}
    )
endif(PNG_FOUND)

if(FFTW3_FOUND)
    set(LIBS ${LIBS}
        ${FFTW3_LIBRARIES}
    )
endif(FFTW3_FOUND)

target_link_libraries(${PROJECT_NAME} ${LIBS})
