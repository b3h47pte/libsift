#!/bin/bash
if [[ ${TRAVIS_OS_NAME} == "linux" ]]; then
elif [[ ${TRAVIS_OS_NAME} == "osx" ]]; then
    brew install boost
fi
