cmake_minimum_required(VERSION 2.8)

set(HRM HeartRateMonitor)
set(HRM_CPP ${HRM}_cpp)
set(HRM_SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/java)
set(HRM_BIN_DIR ${CMAKE_BINARY_DIR}/${HRM})
set(HRM_LIBS_DIR ${HRM_BIN_DIR}/libs/armeabi-v7a)

# HeartRateMonitor native part
include_directories(
    cpp
    )

set(SOURCES
    cpp/HeartRateMonitorPreview.cpp
    cpp/ImageViewHeartRateVisualizer.cpp
    cpp/ImageViewFrameDrawer.cpp
    )
add_library(${HRM_CPP} SHARED ${SOURCES})

set(LIBS
    ${Boost_LIBRARIES} 
    android log jnigraphics
    heartrate
    )
target_link_libraries(${HRM_CPP} ${LIBS})

# HeartRateMonitor android java part
file(GLOB_RECURSE JAVA_SOURCES java/*.*) 

get_target_property(HRM_CPP_ ${HRM_CPP} LOCATION)

add_custom_target(
    ${HRM} ALL
    COMMAND 

        # mkdir all project dirs
        mkdir -p ${HRM_BIN_DIR} ${HRM_LIBS_DIR} &&
        
        # copy symbolic link tree to binary directory
        ls ${HRM_SRC_DIR} | xargs -I {} cp -rsf ${HRM_SRC_DIR}/{} ${HRM_BIN_DIR} &&
        
        # copy native library to libs dir
        cp ${HRM_CPP_} ${HRM_LIBS_DIR} &&
        
        # update android library project 
        android update project -p ${HRM_BIN_DIR} -s -t android-17 > /dev/null &&
        
        # go to project directory 
        cd ${HRM_BIN_DIR} && 
        
        # and build it
        ant clean debug # > /dev/null
    
    DEPENDS ${HRM_CPP} ${JAVA_SOURCES}
)

add_custom_target(
    ${HRM}_output_apk
    COMMAND 
    
        # mkdir all project dirs
        mkdir -p ${APK_OUTPUT} &&
        
        # output apk
        find ${HRM_BIN_DIR} -name *-debug.apk | xargs cp -t ${APK_OUTPUT}
    
    DEPENDS ${HRM}
)

add_custom_target(
    ${HRM}_clean
    COMMAND 

        # mkdir all project dirs
        rm -rf ${HRM_BIN_DIR}

)
