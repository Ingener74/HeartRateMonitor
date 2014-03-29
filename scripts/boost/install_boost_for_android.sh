#!/bin/bash

if [ -z $1 ]
then
    echo "Usage: ./scripts/boost/install_boost_for_android.sh <android-ndk-root>"
else
	pwd_=$PWD
	cd $(readlink -f $(dirname $0))
	cp -R Boost-for-Android $1/sources/third_party/
	cd $1/sources/third_party/Boost-for-Android
	./build-android.sh --boost=1.55.0 $1
fi


 