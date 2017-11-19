#!/bin/bash

echo "Running install.sh..."

if [[ ${TRAVIS_OS_NAME} == "linux" ]]; then
    sudo apt-get -qq update
    sudo apt-get install -y libopenimageio1.3
    sudo apt-get install -y libopenimageio-dev
    dpkg -L libopenimageio-dev
elif [[ ${TRAVIS_OS_NAME} == "osx" ]]; then
    brew update
    brew install homebrew/science/openimageio
fi

echo "    Running C++..."
./cpp/scripts/install.sh
