# Author:                                 Shnaider Pavel
# Soft:                                   Heart Rate Monitor
#
# VARIABLE                             := value1 \
#                                         value2
# 
# to print message do
# $(info    local path = $(LOCAL_PATH))
# $(warning local path = $(LOCAL_PATH))

LOCAL_PATH                             := $(call my-dir)
MY_ROOT                                := $(LOCAL_PATH)

# test_module
include $(LOCAL_PATH)/test_module/Android.mk

# boost
LOCAL_PATH                             := $(MY_ROOT)
include $(LOCAL_PATH)/boost_1_55_0/libs/system/Android.mk
LOCAL_PATH                             := $(MY_ROOT)
include $(LOCAL_PATH)/boost_1_55_0/libs/thread/Android.mk

# Heart Rate Monitor library
include $(CLEAR_VARS)
LOCAL_PATH                             := $(MY_ROOT)

LOCAL_MODULE                           := heartratemonitor

LOCAL_C_INCLUDES                       := $(LOCAL_PATH)/test_module \
                                          $(LOCAL_PATH)/boost_1_55_0
                                          
LOCAL_SRC_FILES                        := HeartRateMonitorPreview.cpp \
                                          HeartRateProcessor.cpp
                                          
LOCAL_STATIC_LIBRARIES                 := test_module boost_system boost_thread

LOCAL_LDLIBS                           := -llog -landroid
include $(BUILD_SHARED_LIBRARY)
$(call import-module test_module)
$(call import-module boost_system)
$(call import-module boost_thread)
