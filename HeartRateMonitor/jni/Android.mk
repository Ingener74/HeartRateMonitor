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
LOCAL_PATH                             := $(MY_ROOT)
include $(LOCAL_PATH)/test_module/Android.mk

# heartbeatrate module
LOCAL_PATH                             := $(MY_ROOT)
include $(LOCAL_PATH)/../../modules/libheartbeatrate/Android.mk

# boost
#LOCAL_PATH                             := $(MY_ROOT)
#include $(LOCAL_PATH)/boost/Android.mk

# Heart Rate Monitor library
include $(CLEAR_VARS)
LOCAL_PATH                             := $(MY_ROOT)

BOOST_PATH := $(LOCAL_PATH)/../../build_android/3RDPARTY
BOOST_LIBS := \
	$(BOOST_PATH)/lib/libboost_atomic-gcc-mt-1_55.a \
	$(BOOST_PATH)/lib/libboost_date_time-gcc-mt-1_55.a \
	$(BOOST_PATH)/lib/libboost_filesystem-gcc-mt-1_55.a \
	$(BOOST_PATH)/lib/libboost_iostreams-gcc-mt-1_55.a \
	$(BOOST_PATH)/lib/libboost_program_options-gcc-mt-1_55.a \
	$(BOOST_PATH)/lib/libboost_regex-gcc-mt-1_55.a \
	$(BOOST_PATH)/lib/libboost_signals-gcc-mt-1_55.a \
	$(BOOST_PATH)/lib/libboost_system-gcc-mt-1_55.a \
	$(BOOST_PATH)/lib/libboost_thread-gcc-mt-1_55.a

LOCAL_MODULE                           := HeartRateMonitor

LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/test_module \
	$(BOOST_PATH)/include \
	$(LOCAL_PATH)/../../modules/libheartbeatrate/include

LOCAL_CPPFLAGS += -fexceptions -frtti

LOCAL_SRC_FILES := \
	HeartRateMonitor.cpp \
	HeartRateMonitorPreview.cpp

LOCAL_STATIC_LIBRARIES := \
	test_module \
	heartbeatrate \
	boost

LOCAL_LDLIBS := \
	-llog -landroid -ljnigraphics $(BOOST_LIBS)

include $(BUILD_SHARED_LIBRARY)
