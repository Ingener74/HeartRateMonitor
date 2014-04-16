#!/bin/bash

function install {
	pwd_=$PWD
	cd $(readlink -f $(dirname $0))
	
	echo "Clean Boost for Android in android ndk directory"
	rm -rf $1/sources/third_party/Boost-for-Android
	
	echo "Copy Boost for Android in android ndk directory"
	cp -R Boost-for-Android $1/sources/third_party/
	
	echo "Go to android ndk directory"
	cd $1/sources/third_party/Boost-for-Android
	echo "i am here $PWD"
	
	echo "Build and install Boost for Android"
	./build-android.sh --boost=1.55.0 --prefix=$1/toolchains/arm-linux-androideabi-4.8/prebuilt/linux-x86_64/user $1
}

if [ -z $1 ]
then
	echo "Usage: ./scripts/boost/install_boost_for_android.sh <android-ndk-root>"
	ndk_dir=$(zenity --file-selection --directory --title="Выбери папку android-ndk")
	if [ -z $ndk_dir ];
	then
		echo "Error"
		exit 1
	fi
	install $ndk_dir
else
	install $1
fi
