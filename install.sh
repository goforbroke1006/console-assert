#!/usr/bin/env bash

#PLATFORM=`uname`

case "$OSTYPE" in
  solaris*) PLATFORM="SOLARIS" ;;
  darwin*)  PLATFORM="OSX" ;;
  linux*)   PLATFORM="LINUX" ;;
  bsd*)     PLATFORM="BSD" ;;
  msys*)    PLATFORM="WINDOWS" ;;
  *)        PLATFORM="unknown: $OSTYPE" ;;
esac


rm -rf build
mkdir build
cd build
cmake ..
make

if [[ "$PLATFORM" == 'LINUX' ]]; then
    sudo make install
else
    make install
fi

echo 'Press any key...'
read