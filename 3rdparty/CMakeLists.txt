cmake_minimum_required(VERSION 2.8)

set(3RDPARTY_BUILD_TYPE Release)
set(3RDPARTY_INSTALL ${CMAKE_BINARY_DIR}/3RDPARTY)

file(MAKE_DIRECTORY ${3RDPARTY_INSTALL})

add_subdirectory(boost)

add_custom_target(
    prepare_repository
    DEPENDS ext_boost
    )
