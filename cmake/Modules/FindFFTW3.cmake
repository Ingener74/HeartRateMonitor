cmake_minimum_required(VERSION 2.8)

find_path (FFTW3_INCLUDE_DIRS fftw3.h)
find_library (FFTW3_LIBRARIES NAMES fftw3)

if(FFTW3_INCLUDE_DIRS AND FFTW3_LIBRARIES)
    set(FFTW3_FOUND TRUE)
    message(STATUS "fftw3 found")
    message(STATUS "fftw3 include dirs ${FFTW3_INCLUDE_DIRS}")
    message(STATUS "fftw3 libraries    ${FFTW3_LIBRARIES}")
endif(FFTW3_INCLUDE_DIRS AND FFTW3_LIBRARIES)

mark_as_advanced (FFTW3_INCLUDE_DIRS FFTW_LIBRARIES)
