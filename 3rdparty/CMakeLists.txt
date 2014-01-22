cmake_minimum_required(VERSION 2.8)

include(ExternalProject)

set(3RDPARTY_BUILD_TYPE Release)
set(3RDPARTY_INSTALL ${CMAKE_BINARY_DIR}/3RDPARTY)

file(MAKE_DIRECTORY ${3RDPARTY_INSTALL})

add_subdirectory(boost)
add_subdirectory(gtest)

set(PREPARE prepare_repository)
if(ANDROID)
add_custom_target(
    ${PREPARE}
    DEPENDS ext_boost 
    )
else()
add_custom_target(
    ${PREPARE}
    DEPENDS ext_gtest
    )
endif()
