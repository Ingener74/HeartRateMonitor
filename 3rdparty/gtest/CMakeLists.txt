cmake_minimum_required(VERSION 2.8)

set(EXT_GTEST ext_gtest)
if(ANDROID)
else()
    ExternalProject_Add(
        ${EXT_GTEST}
        URL ${CMAKE_CURRENT_LIST_DIR}/gtest-1.7.0.zip
        )
endif()

