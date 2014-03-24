cmake_minimum_required(VERSION 2.8)

# include modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/cmake/")
if(ANDROID)
    include(FindAndroidBoost)
else()
endif()

# 3rdparty
set(3RDPARTY_BUILD_TYPE Release)
set(3RDPARTY_INSTALL ${CMAKE_BINARY_DIR}/3RDPARTY)

file(MAKE_DIRECTORY ${3RDPARTY_INSTALL})
file(MAKE_DIRECTORY ${3RDPARTY_INSTALL}/lib)
file(MAKE_DIRECTORY ${3RDPARTY_INSTALL}/include)

include_directories(${3RDPARTY_INSTALL}/include)
link_directories(${3RDPARTY_INSTALL}/lib)
if(ANDROID)
    include_directories(${ANDROID_NDK}/platforms/android-${ANDROID_NATIVE_API_LEVEL}/arch-arm/usr/include)
else()
endif()

add_subdirectory(3rdparty)

add_subdirectory(modules)

add_subdirectory(apps)

add_subdirectory(testing)
