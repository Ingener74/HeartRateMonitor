#!/bin/bash

if [ -z $1 ]
then
    echo "Usage: "
else
    cmake .. -DCMAKE_TOOLCHAIN_FILE=$1 -DCMAKE_BUILD_TYPE=Release -DANDROID_ABI="armeabi-v7a with NEON" -DANDROID_NATIVE_API_LEVEL=14 -DGIT_EXECUTABLE=/usr/bin/git
fi
