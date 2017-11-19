#!/bin/bash

PWD=$(pwd)
cd cpp
mkdir -p build
cd build
cmake ../ -DBUILD_DOCS=OFF
make -j4
make test ARGS=-j4
cd ${PWD}
