#!/bin/bash

# Note this file should not be getting called on Mac in Travis builds...
sudo apt-get install -y zlib1g-dev
sudo apt-get install -y libtiff5 libtiff5-dev
sudo apt-get install -y libpng12-0 libpng12-dev
sudo apt-get install -y libboost-all-dev

tar xvf ilmbase-2.2.0.tar.gz
cd ilmbase-2.2.0
mkdir build
cd build
cmake ../
make -j4
sudo make install
cd ../../

tar xvf openexr-2.2.0.tar.gz
cd openexr-2.2.0
mkdir build
cd build
cmake ../ -DILMBASE_PACKAGE_PREFIX=/usr/local
make -j4
sudo make install
cd ../../

tar xvf oiio-Release-1.7.17.tar.gz
cd oiio-Release-1.7.17
mkdir build
cd build
cmake ../ -DSTOP_ON_WARNING=OFF
make -j4
sudo make install
cd ../../
