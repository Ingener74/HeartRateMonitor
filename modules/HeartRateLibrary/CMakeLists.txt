cmake_minimum_required(VERSION 2.8)

# Cpp part
set(HRL_CPP HeartRateLibrary_cpp)

set(SOURCES
    android_cpp/src/HeartRate.cpp
)

add_library(${HRL_CPP} SHARED ${SOURCES})

set(LIBS
    android
    log
)
target_link_libraries(${HRL_CPP} ${LIBS})

# Java part
set(HRL     HeartRateLibrary)
set(HRL_SRC_DIR ${CMAKE_SOURCE_DIR}/modules/HeartRateLibrary/android_java)
set(HRL_BIN_DIR ${CMAKE_BINARY_DIR}/${HRL})
set(HRL_LIBS_DIR ${HRL_BIN_DIR}/libs/armeabi-v7a)

get_target_property(CPP_ ${HRL_CPP} LOCATION)

add_custom_target(
    ${HRL} ALL
    COMMAND
        # clean
        # rm -rf ${HRL_BIN_DIR} && 
        
        # mkdir all project dirs
        mkdir -p ${HRL_BIN_DIR} ${HRL_LIBS_DIR} && #${HRL_BIN_DIR}/src && 
        
        # copy symbolic link tree to binary directory
        ls ${HRL_SRC_DIR} | xargs -I {} cp -rsf ${HRL_SRC_DIR}/{} ${HRL_BIN_DIR} && 
        
        # copy native library to libs dir
        cp ${CPP_} ${HRL_LIBS_DIR} && 
        
        # update android library project 
        android update lib-project -p ${HRL_BIN_DIR} -t android-17 > /dev/null &&
        
        # go to project directory 
        cd ${HRL_BIN_DIR} && 
        
        # and build it
        ant clean debug > /dev/null # | grep BUILD
    DEPENDS 
        ${HRL_CPP}
)
