#!/bin/bash

echo "Running install.sh..."

if [[ ${TRAVIS_OS_NAME} == "linux" ]]; then
    sudo apt-get -qq update
    ./external/install_oiio.sh
elif [[ ${TRAVIS_OS_NAME} == "osx" ]]; then
    brew update
    brew install homebrew/science/openimageio
fi

echo "    Running C++..."
./cpp/scripts/install.sh
