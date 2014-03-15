cmake_minimum_required(VERSION 2.8)


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

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

add_subdirectory(3rdparty)

add_subdirectory(modules)

add_subdirectory(apps)

add_subdirectory(testing)
