APP_OPTIM := debug
APP_PLATFORM := android-14
APP_STL := gnustl_static
APP_CPPFLAGS += -frtti -fexceptions -DANDROID -std=c++11
#APP_ABI := armeabi armeabi-v7a x86
APP_ABI := armeabi-v7a
APP_MODULES := HeartRateMonitor
NDK_TOOLCHAIN_VERSION := 4.8
#NDK_TOOLCHAIN_VERSION := clang3.3
