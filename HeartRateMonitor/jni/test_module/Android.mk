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

$(info    local path = $(LOCAL_PATH))

include $(CLEAR_VARS)
LOCAL_MODULE                           := test_module
LOCAL_SRC_FILES                        := IModule.cpp \
                                          TestModule.cpp
LOCAL_EXPORT_C_INCLUDES                := $(LOCAL_PATH)

include $(BUILD_STATIC_LIBRARY)
