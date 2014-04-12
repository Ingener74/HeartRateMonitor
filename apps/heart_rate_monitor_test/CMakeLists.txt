cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME heart_rate_monitor_test)
project(${PROJECT_NAME})

include_directories(
    ../../modules/libheartrate/include
)

set(SOURCES 
    src/main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} ${OpenCV_LIBRARIES} heartrate)
