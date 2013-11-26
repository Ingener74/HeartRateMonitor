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

$(info    building boost_thread)

include $(CLEAR_VARS)
LOCAL_MODULE                           := boost_thread
LOCAL_SRC_FILES                        := src/future.cpp \
                                          src/tss_null.cpp \
                                          src/pthread/once_atomic.cpp \
                                          src/pthread/once.cpp \
                                          src/pthread/thread.cpp

LOCAL_C_INCLUDES                       := $(LOCAL_PATH)/../../

include $(BUILD_STATIC_LIBRARY)
