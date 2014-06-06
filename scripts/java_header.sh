#!/bin/bash

echo "Generate C++ header from Java"

header_file=$(zenity --file-selection --save --title='Save header to file')
bin_dir=$(zenity --file-selection --directory --title='Select bin classes directory')
android_sdk=$(zenity --file-selection --directory --title='Select android SDK directory')
class=$(zenity --entry --text=Enter java class, example: com.example.MainActivity)

# if [-e jh.cfg ];
#then
#    echo 'Config file exist'
#    cat jh.cfg | while read line; 
#    do
#    done
#else
#    echo 'Config not exist'
#    echo $header_file >> .jh.cfg
#    echo $bin_dir >> jh.cfg
#    echo $android_sdk >> jh.cfg
#    echo $class >> jh.cfg
#fi

javah -jni -o $header_file -classpath $bin_dir:$(find $android_sdk -name android.jar | grep '17') $class
