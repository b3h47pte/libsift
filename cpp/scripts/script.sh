#!/bin/bash

PWD=$(pwd)
cd cpp
mkdir -p build
cd build
cmake ../
make
cd ${PWD}
