cmake_minimum_required(VERSION 2.8)

set(3RDPARTY_BUILD_TYPE Release)
set(3RDPARTY_INSTALL ${CMAKE_BINARY_DIR}/3RDPARTY)

file(MAKE_DIRECTORY ${3RDPARTY_INSTALL})
file(MAKE_DIRECTORY ${3RDPARTY_INSTALL}/lib)
file(MAKE_DIRECTORY ${3RDPARTY_INSTALL}/include)

if(ANDROID)
    include_directories(${3RDPARTY_INSTALL}/include/boost-1_55)
    link_directories(${3RDPARTY_INSTALL}/lib)
else()
    include_directories(${3RDPARTY_INSTALL}/include)
    link_directories(${3RDPARTY_INSTALL}/lib)
endif()

add_subdirectory(3rdparty)

add_subdirectory(modules)

add_subdirectory(apps)

add_subdirectory(tests)
