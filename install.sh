#!/usr/bin/env bash

rm -rf build
mkdir build
cd build
cmake ..
make
make install

echo 'Press any key...'
read