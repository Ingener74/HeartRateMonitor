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

BOOST_PATH := $(LOCAL_PATH)/../../build_android/3RDPARTY

LOCAL_C_INCLUDES                       := $(LOCAL_PATH)/include \
                                          $(BOOST_PATH)/include

LOCAL_MODULE                           := heartbeatrate
LOCAL_SRC_FILES := \
	src/AndroidLog.cpp \
	src/HeartBeatRateTypes.cpp \
	src/HeartRateProcessor.cpp \
	src/HeartRateTools.cpp \
	src/NV21FrameSource.cpp \
	src/RGBFrameSource.cpp \
	src/SimpleHeartRateGenerator.cpp \
	src/SimpleHeartRateVisualizer.cpp \
	src/HeartRateCounter.cpp \
	src/ImageViewHeartRateVisualizer.cpp \
	src/ImageViewImageDrawer.cpp \
	src/RGBHeartRateGenerator.cpp

LOCAL_EXPORT_C_INCLUDES                := $(LOCAL_PATH)

include $(BUILD_STATIC_LIBRARY)
