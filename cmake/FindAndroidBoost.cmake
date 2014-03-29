cmake_minimum_required(VERSION 2.8.8)

set(AndroidBoost_FOUND        FALSE)
set(AndroidBoost_INCLUDE_DIR  )
set(AndroidBoost_LIB_DIR      )
set(AndroidBoost_LIBRARIES
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

if(AndroidBoost_INCLUDE_DIR AND AndroidBoost_LIB_DIR)
    set(AndroidBoost_FOUND TRUE)
else(AndroidBoost_INCLUDE_DIR AND AndroidBoost_LIB_DIR)
    set(AndroidBoost_FOUND FALSE)
endif(AndroidBoost_INCLUDE_DIR AND AndroidBoost_LIB_DIR)

mark_as_advanced(AndroidBoost_INCLUDE_DIR AndroidBoost_LIB_DIR)

if(AndroidBoost_FOUND)
    message(STATUS "Boost for Android found : found")
    message(STATUS " - include dir          : ${AndroidBoost_INCLUDE_DIR}")
    message(STATUS " - library dir          : ${AndroidBoost_LIB_DIR}")
    message(STATUS " - libraries            : ${ABOOST_LIBRARIES}")
else(AndroidBoost_FOUND)
    message(FATAL_ERROR "Boost for Android found: not found")
endif(AndroidBoost_FOUND)
