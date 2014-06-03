#!/bin/bash

get_directory() {
	apk_dir=$(zenity --file-selection --directory --title="Выбери директорию с APK файлами")
	if [ -z apk_dir ];
	then
		echo "error: directory not selected"
		exit 1
	fi
	echo $apk_dir
}

get_apk_names() {
	echo $(find $1 -name *.apk | xargs -i basename {})
}

get_apk_paths() {
	echo $(find $1 -name *.apk)
}

get_path() {
    echo $1 | grep $2
}

if [ -z $1 ];
then
	echo "Usage: ./install_apk <directory>"
	apk_directory=$(get_directory)
else
	apk_directory=$1
fi

# apk_paths=$(get_apk_names $apk_directory)
# apk_names=$(get_apk_paths $apk_directory)
#
# echo "apk names: "
# echo "$apk_names"
# echo "$apk_paths"
#
# apk_select=$(zenity --list --checklist --multiple --width=1000 --height=600 \
# 				--title="Выбор необходимые для установки APK файлы" \
# 				--column="Какие ебануть" --column="Файл" \
# 				--print-column="2" --separator=";" \
# 				$(echo $(get_apk_names $apk_directory) | xargs -i echo "FALSE {}"))
#
# echo "selected names $apk_select"
#
# # apk_paths_selected=$(echo $apk_select | xargs -d ';' echo | grep )
# echo "selected path = $(echo $apk_select | xargs -d ';' -i get_path {} $apk_paths)"
#
# exit 0

selected_apk=$(zenity --list --checklist --multiple --width=1000 --height=600 \
				--title="Выбори необходимые для установки APK файлы" \
				--column="Твой выбор" --column="какашка APK'шка" \
				--print-column="2" --separator=";" \
				$(find $apk_directory -name *.apk | xargs -i echo "FALSE {}"))
if [ -z $selected_apk ];
then 
	echo "error: apk's are not selected"
	exit 1
fi

adb_device=`zenity --list --radiolist --width=500 --height=200 \
				--title="Выбери устройство для установки" \
				--column="Твой выбор мудила" --column="куда ебашить" \
				$(adb devices | awk '{print $1}' | awk 'NR > 1' | xargs -i echo "FALSE {}")`
if [ -z $adb_device ];
then 
	echo "error: device not selected"
	exit 1
fi

echo $selected_apk | tr ';' '\n' | xargs -i adb -s $adb_device install -r {}

