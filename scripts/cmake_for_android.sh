#!/bin/bash

function do_cmake {
	cmake .. -DCMAKE_TOOLCHAIN_FILE=$1 -DCMAKE_BUILD_TYPE=Release -DANDROID_ABI="armeabi-v7a with NEON" -DANDROID_NATIVE_API_LEVEL=14 -DLIBRARY_OUTPUT_PATH=$PWD/libs/armeabi-v7a -DLIBRARY_OUTPUT_PATH_ROOT=$PWD
}

if [ -z $1 ];
then
	echo "Usage: ../scripts/cmake_for_android.sh <android-toolchain-file>"
	toolchain_file=$(zenity --file-selection --title="Выбери файл android.toolchain.cmake")
	if [ -z $toolchain_file ];
	then
		echo "Error"
		exit 1
	fi
	do_cmake $toolchain_file
else
	do_cmake $1
fi
