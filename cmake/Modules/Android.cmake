cmake_minimum_required(VERSION 2.8)

message(STATUS "Heart rate monitor for Android")

set(APK_OUTPUT ${CMAKE_SOURCE_DIR}/apk_output)
message(STATUS " * ready apk storage ${APK_OUTPUT}")

include_directories(${ANDROID_NDK}/platforms/android-${ANDROID_NATIVE_API_LEVEL}/arch-arm/usr/include)
