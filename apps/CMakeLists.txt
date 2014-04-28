cmake_minimum_required(VERSION 2.8)

if(MINGW AND NOT ANDROID)

    if(OpenCV_FOUND)

        add_subdirectory(HeartRateMonitor_MinGW)

    endif()

endif()

if(ANDROID)
    
    add_subdirectory(HeartRateMonitor)
    
else()
    
    if(OpenCV_FOUND AND FFTW3_FOUND)
    
        add_subdirectory(heart_rate_monitor_test)
        
        add_subdirectory(fftw_test_app)
        
    endif()
    
endif()
