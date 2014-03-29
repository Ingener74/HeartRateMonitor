cmake_minimum_required(VERSION 2.8.8)

set(ABOOST_FOUND FALSE)

if(ABOOST_INCLUDE_DIR AND ABOOST_LIB_DIR)
    set(ABOOST_FOUND TRUE)
else(ABOOST_INCLUDE_DIR AND ABOOST_LIB_DIR)

    find_path(ABOOST_INCLUDE_DIR_ 
        NAMES
            chrono.hpp
            foreach.hpp
            format.hpp
            function.hpp
            signals2.hpp
            smart_ptr.hpp
            thread.hpp
        PATHS
            ${ANDROID_NDK}/sources/third_party/Boost-for-Android/build/include/boost-1_55
        PATH_SUFFIXES
            boost
    )
    find_path(ABOOST_LIB_DIR_
        NAMES
            libboost_system-gcc-mt-1_55.a
            libboost_thread-gcc-mt-1_55.a
        PATHS
            ${ANDROID_NDK}/sources/third_party/Boost-for-Android/build/lib
    )
    
#    if(ABOOST_LIB_DIR_)
#        find_library(ABOOST_SYSTEM
#            NAMES
#                boost_system
#                boost_system-gcc-mt-1_55
#            PATHS 
#                /home/ingener/dev/android-ndk-r9d/sources/third_party/Boost-for-Android/build/lib
#            NO_DEFAULT_PATH
#        )
#        set(ABOOST_LIBRARIES ${ABOOST_SYSTEM})
#        message(STATUS "libraries ${ABOOST_SYSTEM}")
#    endif(ABOOST_LIB_DIR_)

    set(ABOOST_INCLUDE_DIR ${ABOOST_INCLUDE_DIR_})
    set(ABOOST_LIB_DIR     ${ABOOST_LIB_DIR_})
    set(ABOOST_LIBRARIES
        boost_atomic-gcc-mt-1_55
        boost_date_time-gcc-mt-1_55
        boost_filesystem-gcc-mt-1_55
        boost_iostreams-gcc-mt-1_55
        boost_program_options-gcc-mt-1_55
        boost_regex-gcc-mt-1_55
        boost_signals-gcc-mt-1_55
        boost_system-gcc-mt-1_55
        boost_thread-gcc-mt-1_55
    )
    
    if(ABOOST_INCLUDE_DIR AND ABOOST_LIB_DIR)
        set(ABOOST_FOUND TRUE)
    endif(ABOOST_INCLUDE_DIR AND ABOOST_LIB_DIR)
    
    mark_as_advanced(ABOOST_INCLUDE_DIR ABOOST_LIB_DIR)

endif(ABOOST_INCLUDE_DIR AND ABOOST_LIB_DIR)

if(ABOOST_FOUND)
    message(STATUS "Boost for Android found : found")
    message(STATUS " - include dir          : ${ABOOST_INCLUDE_DIR}")
    message(STATUS " - library dir          : ${ABOOST_LIB_DIR}")
    message(STATUS " - libraries            : ${ABOOST_LIBRARIES}")
else(ABOOST_FOUND)
    message(FATAL_ERROR "Boost for Android found: not found")
endif(ABOOST_FOUND)

