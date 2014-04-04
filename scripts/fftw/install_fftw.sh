#!/bin/bash

ARCHIVE=$(zenity --file-selection --title="Выбери файл с исходниками fftw")
if [ -z $ARCHIVE ];
then
	echo "Error: source archive not selected"
	exit 1
fi

NDK_DIR=$(zenity --file-selection --directory --title="А теперь выбери директорию android ndk")
if [ -z $NDK_DIR ];
then
	echo "Error: ndk directory not selected"
	exit 1
fi

PREFIX_DIR=$NDK_DIR/toolchains/arm-linux-androideabi-4.8/prebuilt/linux-x86_64/user

rm -rf $NDK_DIR/sources/third_party/fftw && \
	mkdir -p $NDK_DIR/sources/third_party/fftw && \
	tar xfv $ARCHIVE -C $NDK_DIR/sources/third_party/fftw

SRC_DIR=$(dirname $(find $NDK_DIR/sources/third_party/fftw -name configure))
if [ -z $SRC_DIR ];
then
	echo "Error: source dir not selected"
	exit 1
fi
echo "Source dir $SRC_DIR"

SYSROOT_DIR=$(zenity --file-selection --directory --title="Найди директорию sys-root")
if [ -z $SYSROOT_DIR ];
then
	echo "Prefix dir $SYSROOT_DIR"
	exit 1
fi
echo "System root dir $SYSROOT_DIR"

#cd $SRC_DIR
#export PATH="$NDK_DIR/toolchains/arm-linux-androideabi-4.8/prebuilt/linux-x86_64/bin/:$PATH"
#export SYS_ROOT=$SYSROOT_DIR
#export CC="arm-linux-androideabi-gcc --sysroot=$SYS_ROOT"
#export LD="arm-linux-androideabi-ld"
#export AR="arm-linux-androideabi-ar"
#export RANLIB="arm-linux-androideabi-ranlib"
#export STRIP="arm-linux-androideabi-strip"

#./configure --host=arm-eabi --build=i386-apple-darwin10.8.0 --prefix=$INSTALL_DIR LIBS="-lc -lgcc"
#./configure --host=arm-eabi --prefix=$INSTALL_DIR --enable-neon

#make
#make install

#exit 0