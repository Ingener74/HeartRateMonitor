cmake_minimum_required(VERSION 2.8)

# include modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/cmake/")
if(ANDROID)

    include(FindAndroidBoost)
    if(ABOOST_FOUND)
        include_directories(${ABOOST_INCLUDE_DIR})
        link_directories(${ABOOST_LIB_DIR})
    endif(ABOOST_FOUND)
    
    include_directories(${ANDROID_NDK}/platforms/android-${ANDROID_NATIVE_API_LEVEL}/arch-arm/usr/include)

else(ANDROID)

    find_package(Boost 1.53.0 REQUIRED)
    find_package(GTest)
    
endif(ANDROID)

add_definitions(-std=c++11)

add_subdirectory(modules)

add_subdirectory(apps)
