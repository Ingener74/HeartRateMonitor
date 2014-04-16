cmake_minimum_required(VERSION 2.8)

if(ANDROID)
    
    add_subdirectory(HeartRateMonitor)
    
else()
    
    if(OpenCV_FOUND)
    
        add_subdirectory(heart_rate_monitor_test)
        
    endif(OpenCV_FOUND)
    
endif()