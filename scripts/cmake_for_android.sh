#!/bin/bash

if [ -z $1 ]
then
    echo "Usage: "
else
    cmake .. -DCMAKE_TOOLCHAIN_FILE=$1 -DCMAKE_BUILD_TYPE=Release -DANDROID_ABI="armeabi-v7a with NEON" -DANDROID_NATIVE_API_LEVEL=14 -DLIBRARY_OUTPUT_PATH=$PWD/libs/armeabi-v7a -DLIBRARY_OUTPUT_PATH_ROOT=$PWD
fi

# insert when could added executables
# -DEXECUTABLE_OUTPUT_PATH=$PWD/bin 
