cmake_minimum_required(VERSION 2.8)

set(HRM HeartRateMonitor)
set(HRM_CPP ${HRM}_cpp)
set(HRM_SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/java)
set(HRM_BIN_DIR ${CMAKE_BINARY_DIR}/${HRM})
set(HRM_LIBS_DIR ${HRM_BIN_DIR}/libs/armeabi-v7a)

# HeartRateMonitor native part
include_directories(
    cpp
    ../../modules/libheartbeatrate/include
    )

set(SOURCES
    cpp/HeartRateMonitorPreview.cpp
    cpp/ImageViewHeartRateVisualizer.cpp
    cpp/ImageViewImageDrawer.cpp
    )
add_library(${HRM_CPP} SHARED ${SOURCES})

target_link_libraries(${HRM_CPP} ${AndroidBoost_LIBRARIES} android log jnigraphics)

set(LIBS
    heartbeatrate
    )
target_link_libraries(${HRM_CPP} ${LIBS})

# HeartRateMonitor android java part
add_custom_command(
    OUTPUT clean_prj
    COMMAND rm -rf ${HRM_BIN_DIR}
    )
add_custom_command(
    OUTPUT mkdir_bin_dir
    COMMAND mkdir -p ${HRM_BIN_DIR}
    )
add_custom_command(
    OUTPUT copy_symlink_tree
    COMMAND ls ${HRM_SRC_DIR} | xargs -I {} cp -rsf ${HRM_SRC_DIR}/{} ${HRM_BIN_DIR}
    )
add_custom_command(
    OUTPUT mkdir_libs_dir
    COMMAND mkdir -p ${HRM_LIBS_DIR}
    )
get_target_property(HRM_CPP_ ${HRM_CPP} LOCATION)
add_custom_command(
    OUTPUT copy_libs
    COMMAND cp ${HRM_CPP_} ${HRM_LIBS_DIR}
    )
add_custom_command(
    OUTPUT update_prj
    COMMAND android update project -p . -s -t android-17 > /dev/null
    WORKING_DIRECTORY ${HRM_BIN_DIR}
    )
add_custom_command(
    OUTPUT build_prj
    COMMAND ant clean > /dev/null && ant debug | grep BUILD
    WORKING_DIRECTORY ${HRM_BIN_DIR}
    )
add_custom_command(
    OUTPUT mkdir_apk_output
    COMMAND mkdir -p ${APK_OUTPUT}
    )
add_custom_command(
    OUTPUT copy_output_apk
    COMMAND find ${HRM_BIN_DIR} -name *-debug.apk | xargs cp -t ${APK_OUTPUT}
    )

# linking
add_custom_target(
    ${HRM}
    DEPENDS ${HRM_CPP} mkdir_bin_dir copy_symlink_tree mkdir_libs_dir copy_libs update_prj build_prj mkdir_apk_output copy_output_apk
    )
add_custom_target(
    ${HRM}_develop
    DEPENDS ${HRM_CPP} mkdir_bin_dir copy_symlink_tree mkdir_libs_dir copy_libs update_prj
    )
add_custom_target(
    ${HRM}_clean
    DEPENDS clean_prj
    )
