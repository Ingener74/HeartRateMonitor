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

include $(call all-subdir-makefiles)

# Heart Rate Monitor library
include $(CLEAR_VARS)
LOCAL_PATH                             := $(MY_ROOT)

LOCAL_MODULE                           := heartratemonitor
LOCAL_C_INCLUDES                       := $(LOCAL_PATH)/test_module
LOCAL_SRC_FILES                        := HeartRateMonitorPreview.cpp \
                                          HeartRateProcessor.cpp
LOCAL_LDLIBS                           := -llog -landroid
include $(BUILD_SHARED_LIBRARY)
$(call import-module test_module)
