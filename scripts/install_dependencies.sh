#!/bin/bash

echo "Usage: ./install_dependencies.sh            -- install all dependencies for environment"
echo "Usage: ./install_dependencies.sh java8      -- install java8 from ppa"

case "$1" in 
	"java8")
			sudo add-apt-repository ppa:webupd8team/java
			sudo apt-get update
			sudo apt-get install oracle-java8-installer
	;;
	*)
			sudo apt-get install ant libbz2-dev libboost-dev libgtest-dev libgtk2.0-dev pkg-config lib32stdc++6 lib32z1
	;;
esac
