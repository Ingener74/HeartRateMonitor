cmake_minimum_required(VERSION 2.8)

if(ANDROID)
    
    add_subdirectory(HeartRateMonitor)
    
else()
    
    if(OpenCV_FOUND AND FFTW3_FOUND)
    
        add_subdirectory(heart_rate_monitor_test)
        
        add_subdirectory(fftw_test_app)
        
    endif(OpenCV_FOUND AND FFTW3_FOUND)
    
endif()