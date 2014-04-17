cmake_minimum_required(VERSION 2.8)

add_subdirectory(libheartrate)
if(ANDROID)
    add_subdirectory(HeartRateLibrary)
endif(ANDROID)
