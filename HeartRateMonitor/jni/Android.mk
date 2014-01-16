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


# Heart Rate Monitor library
include $(CLEAR_VARS)
LOCAL_PATH                             := $(MY_ROOT)

LOCAL_ALLOW_UNDEFINED_SYMBOLS := true
BOOST_LIBS := \
	$(LOCAL_PATH)/boost/lib/libboost_atomic-gcc-mt-1_55.a \
	$(LOCAL_PATH)/boost/lib/libboost_date_time-gcc-mt-1_55.a \
	$(LOCAL_PATH)/boost/lib/libboost_filesystem-gcc-mt-1_55.a \
	$(LOCAL_PATH)/boost/lib/libboost_iostreams-gcc-mt-1_55.a \
	$(LOCAL_PATH)/boost/lib/libboost_program_options-gcc-mt-1_55.a \
	$(LOCAL_PATH)/boost/lib/libboost_regex-gcc-mt-1_55.a \
	$(LOCAL_PATH)/boost/lib/libboost_signals-gcc-mt-1_55.a \
	$(LOCAL_PATH)/boost/lib/libboost_system-gcc-mt-1_55.a \
	$(LOCAL_PATH)/boost/lib/libboost_thread-gcc-mt-1_55.a \

LOCAL_MODULE                           := heartratemonitor

LOCAL_C_INCLUDES                       := $(LOCAL_PATH)/test_module \
                                          $(LOCAL_PATH)/boost/include/boost-1_55

LOCAL_SRC_FILES                        := HeartRateMonitorPreview.cpp \
                                          HeartRateProcessor.cpp

LOCAL_STATIC_LIBRARY := $(BOOST_LIBS)
include $(PREBUILD_STATIC_LIBRARY)

LOCAL_STATIC_LIBRARIES                 := test_module
LOCAL_LDLIBS                           := -llog -landroid $(BOOST_LIBS)

LOCAL_CPPFLAGS += -fexceptions
LOCAL_CPPFLAGS += -frtti

include $(BUILD_SHARED_LIBRARY)
$(call import-module test_module)
