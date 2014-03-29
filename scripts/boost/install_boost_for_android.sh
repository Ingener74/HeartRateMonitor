#!/bin/bash

if [ -z $1 ]
then
    echo "Usage: ./scripts/boost/install_boost_for_android.sh <android-ndk-root>"
else
    # cmake .. -DCMAKE_TOOLCHAIN_FILE=$1 -DCMAKE_BUILD_TYPE=Release -DANDROID_ABI="armeabi-v7a with NEON" -DANDROID_NATIVE_API_LEVEL=14 -DLIBRARY_OUTPUT_PATH=$PWD/libs/armeabi-v7a -DLIBRARY_OUTPUT_PATH_ROOT=$PWD
	pwd_=$PWD
	cd $(readlink -f $(dirname $0))
	cp -R Boost-for-Android $1/sources/third_party/
	cd $1/sources/third_party/Boost-for-Android
	./build-android.sh --boost=1.55.0 $1
fi


 