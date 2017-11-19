#!/bin/bash

PWD=$(pwd)
cd cpp
mkdir -p build
cd build
cmake ../ -DBUILD_DOCS=OFF
if [ $? -ne 0 ]; then
    exit 1
fi
make -j4
if [ $? -ne 0 ]; then
    exit 1
fi
make test ARGS=-j4
if [ $? -ne 0 ]; then
    exit 1
fi
cd ${PWD}
