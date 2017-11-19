#!/bin/bash
if [[ ${TRAVIS_OS_NAME} == "linux" ]]; then
    sudo apt-get install -y libboost-all-dev
elif [[ ${TRAVIS_OS_NAME} == "osx" ]]; then
    brew install boost
fi
