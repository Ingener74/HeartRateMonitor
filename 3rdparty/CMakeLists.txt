cmake_minimum_required(VERSION 2.8)

if(ANDROID)
    set(PREPARE prepare_repository)
    include(ExternalProject)
    
    add_subdirectory(boost)
    add_subdirectory(gtest)
    add_custom_target(
        ${PREPARE}
        DEPENDS ext_boost 
        )
else()

    find_package(Boost 1.53.0 REQUIRED)
    find_package(GTest)

endif()
