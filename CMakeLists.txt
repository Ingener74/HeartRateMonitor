cmake_minimum_required(VERSION 2.8)

# include modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/cmake/Modules")

if(ANDROID)

    include(Android)

endif(ANDROID)

# find boost
set(Boost_USE_STATIC_LIBS    ON)
set(Boost_USE_MULTITHREADED  ON)
set(Boost_COMPILER -gcc)
find_package(Boost 1.53.0 REQUIRED 
    COMPONENTS 
        system 
        thread
)

# find fftw
find_package(FFTW3)
if(FFTW3_FOUND)
    add_definitions(-DFFTW3_FOUND)
    include_directories(
        ${FFTW3_INCLUDE_DIRS}
    )
endif(FFTW3_FOUND)

# find OpenCV
find_package(OpenCV 
    COMPONENTS 
        core 
        imgproc 
        highgui
)

# find gtest
find_package(GTest)

# find png
find_package(PNG)
if(PNG_FOUND)
    add_definitions(-DPNG_FOUND)
endif(PNG_FOUND)

# include dependencies
include_directories(
    ${Boost_INCLUDE_DIRS}
    ${OpenCV_INCLUDE_DIRS}
    ${PNG_INCLUDE_DIRS}
)

# include modules
include_directories(
    ${CMAKE_SOURCE_DIR}/modules/libheartrate/include
)

add_definitions(
    -std=c++11 -pedantic # -Wall -Wextra
    ${PNG_DEFINITIONS}
)

add_subdirectory(modules)

add_subdirectory(apps)
