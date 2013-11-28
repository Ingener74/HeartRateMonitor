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

include $(CLEAR_VARS)
LOCAL_MODULE                           := boost_system
LOCAL_SRC_FILES                        := src/error_code.cpp
LOCAL_C_INCLUDES                       := $(LOCAL_PATH)/../../

include $(BUILD_STATIC_LIBRARY)
