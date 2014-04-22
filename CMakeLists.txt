cmake_minimum_required(VERSION 2.8)

# include modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/cmake/Modules")

if(ANDROID)

    include(Android)

endif(ANDROID)

# find boost
set(Boost_USE_STATIC_LIBS    ON)
set(Boost_USE_MULTITHREADED  ON)
if(MINGW)
	set(Boost_COMPILER -mgw48)
else(MINGW)
	set(Boost_COMPILER -gcc)
endif(MINGW)
find_package(Boost 1.53.0 REQUIRED COMPONENTS system thread)

# find fftw
find_package(FFTW)

# find OpenCV
find_package(OpenCV COMPONENTS core imgproc highgui)

# find gtest
find_package(GTest)

# find png
find_package(PNG)
if(PNG_FOUND)
    add_definitions(-DPNG_FOUND)
endif(PNG_FOUND)

include_directories(
    ${Boost_INCLUDE_DIRS}
    ${OpenCV_INCLUDE_DIRS}
    ${PNG_INCLUDE_DIRS}
)

add_definitions(-std=c++11)

add_subdirectory(modules)

add_subdirectory(apps)
