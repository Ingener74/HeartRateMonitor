#!/bin/bash

_pwd=$PWD
echo $_pwd
# clone boost for android
git clone git@github.com:MysticTreeGames/Boost-for-Android.git

echo 'go to Boost-for-Android'
cd Boost-for-Android

# build boost
echo 'Download and build boost'
./build-android.sh ~/dev/android-ndk-r8e --boost=1.55.0

echo 'cp boost in heart rate monitor directory'
mkdir ../HeartRateMonitor/jni/boost
cp build/* ../HeartRateMonitor/jni/boost

cd $_pwd
rm -rf Boost-for-Android
