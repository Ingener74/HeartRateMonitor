cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME HeartRateMonitor_MinGW)
project(${PROJECT_NAME})

set(SOURCES
    src/main.cpp
)
add_executable(${PROJECT_NAME} ${SOURCES})

set(LIBS
    ${Boost_LIBRARIES} ${OpenCV_LIBRARIES} heartrate
)
target_link_libraries(${PROJECT_NAME} ${LIBS})
